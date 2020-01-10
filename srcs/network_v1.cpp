#include "network.hpp"

void	Network::print()
{
	for (int i = 0; i < this->size; i++){
		this->layer[i].weight.print();
		this->layer[i].bias.print();
	}
}

void	Network::shape()
{
	for (int i = 0; i < this->size; i++){
		this->layer[i].weight.shape();
		this->layer[i].bias.shape();
	}
}

double	sigmoid(double x)
{
	return (1.0 / (1.0  + exp(-x)));
}

double	sigmoidPrim(double x)
{
	double	z;
	z = sigmoid(x);
	return (z * (1.0 - z));
}

double	relu(double x)
{
	return (x  > 0.0 ? x : 0.0);
}

double	reluPrim(double x)
{
	return (x > 0.0 ? 1.0 : 0.0);
}
double	leakyRelu(double x)
{
	return (x > 0.0 ? x : 0.01 * x);
}
double	leakyReluPrim(double x)
{
	return (x < 0 ? 0.01  : 1);
}

Matrix	crossEntropyPrim(Matrix	out, Matrix label)
{
	Matrix	res(out.row, out.col);
	double y;
	double o;

	for (int i = 0; i < out.row; i++)
	{
		y = label.tab[i][0];
		o = out.tab[i][0];
		o = o == 0 ? EPSILON : o == 1 ? 1 - EPSILON : o;
		res.tab[i][0] = -1 * (y  * (1 / o) + (1 - y) * (1 / (1 - o)));
	}
	return res;
}

Matrix	softmaxPrim(Matrix	s)
{
	double sum ;
	Matrix	res(s.row, s.col);

	sum = 0;
	for (int i = 0; i < s.row; i++){
		sum += exp(s.tab[i][0]);
	}
	for (int i = 0; i < s.row; i++){
		res.tab[i][0] = (exp(s.tab[i][0]) * (sum - exp(s.tab[i][0]))) / (sum * sum);
	}
	return res;
}

void	softmax(Matrix	*s)
{
	double sum ;

	sum = 0;
	for (int i = 0; i < s->row; i++){
		sum += exp(s->tab[i][0]);
	}
	for (int i = 0; i < s->row; i++){
		s->tab[i][0] = exp(s->tab[i][0]) / sum;
	}
}

static double clip(double x, double min , double max)
{
	return (x < min ? min : x > max ? max : x);
}

double	Network::getError(Matrix out, Matrix label)
{
	double sum;

	sum = 0;
	for (int i = 0; i < out.row; i++){
		sum += 0.5 * pow((label.tab[i][0] - out.tab[i][0]), 2);
	}
	return (sum);
}

double	Network::crossEntropy(Matrix out, Matrix label)
{
	double sum;
	double o, y;

	sum = 0.0;
	for (int i = 0; i < out.row; i++)
	{
		o = out.tab[i][0];
		y = label.tab[i][0];
		sum -= (y * log10(o == 0 ? EPSILON : o) +
				( 1 - y) * log10(1 - o == 0 ? 1 - o + EPSILON: 1 - o));
	}
	return (sum);
}

Matrix	Network::feedForward_v1(Matrix	inputs)
{
	Matrix	in;

	in = inputs;
	for (int i = 0; i < this->size; i++){

		this->layer[i].activation = this->layer[i].weight.mult(in);
		this->layer[i].activation = this->layer[i].activation.add(this->layer[i].bias);
		this->layer[i].beforActivation = this->layer[i].activation.clone();
		this->layer[i].activation.map(&sigmoid);
		in  = this->layer[i].activation;
	}
	return (in);
}

void	Network::backPropagation_v1(Matrix inputs, Matrix labels, double lr, double n)
{
	int	len;
	vector<Matrix>	delta_w;
	vector<Matrix>	delta_b;
	Matrix			delta;
	Matrix			sp;
	Matrix			out;

	len = this->size - 1;
	out = this->feedForward_v1(inputs);
	delta = out.sub(labels);
	sp = this->layer[len].beforActivation;
	sp.map(&sigmoidPrim);
	delta = delta.prod(sp);
	delta_b.push_back(delta);
	delta_w.push_back(delta.mult((layer[len - 1].activation).transpose()));
	for (int i = len - 1; i >= 0; i--)
	{
		sp = this->layer[i].beforActivation.clone();
		sp.map(&sigmoidPrim);
		Matrix trans = this->layer[i + 1].weight.transpose();
		delta = trans.mult(delta);
		delta = delta.prod(sp);
		delta = delta.prod(sp);
		delta_b.push_back(delta);

		if (i - 1 >= 0)
			delta_w.push_back(delta.mult((layer[i - 1].activation).transpose()));
		else
			delta_w.push_back(delta.mult((inputs).transpose()));
	}
	for (int i = 0; i < this->size; i++)
	{
		delta_w[this->size - 1 - i].scale(lr);
		delta_b[this->size - 1 - i].scale(lr);
		this->layer[i].weight = this->layer[i].weight.sub(delta_w[this->size - 1 -i]);
		this->layer[i].bias = this->layer[i].bias.sub(delta_w[this->size - 1 -i]);
	}
}

static int	get_index(Matrix tmp)
{
	int	m = 0;
	double	big = tmp.tab[0][0];

	for (int i = 0; i < tmp.row; i++)
	{
		if (tmp.tab[i][0] > big)
		{
			m = i;
			big = tmp.tab[i][0];
		}
	}
	return m;
}

void	Network::sgd_v1(struct Data* training_data, int epochs, int mini_batch_size, double lr, struct Data* test_data = NULL)
{
	struct Data *training;
	struct Data	*test;
	int		test_size;
	int		good;
	Matrix	res;

	if (test_data)
		test_size = len_data(test_data);
	for (int j = 1; j <= epochs; j++)
	{
		good = 0;
		test = test_data;
		training = training_data;
		while (training)
		{
			this->backPropagation_v1(training->input, training->label, lr, mini_batch_size);
			training = training->next;
		}
		while (test)
		{
			res = this->feedForward_v1(test->input);
			if (get_index(test->label) == get_index(res))
				good++;
			test = test->next;
		}
		cout << "Epoch " << j << " : {" << good << " / " << test_size << "}.\n";
	}
}
