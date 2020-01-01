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

Matrix	crossEntropyPrim(Matrix	out, Matrix label)
{
	Matrix	res(out.row, out.col);
	double y;
	double o;

	for (int i = 0; i < out.row; i++)
	{
		y = label.tab[i][0];
		o = out.tab[i][0];
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

	sum = 0.0;
	for (int i = 0; i < out.row; i++)
	{
		sum -= (label.tab[i][0] * log10(out.tab[i][0]) +
				( 1 - label.tab[i][0]) * log10(1 - out.tab[i][0]));
	}
	return (sum);
}

Matrix	Network::feedForward(Matrix	inputs)
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

void	Network::backPropagation(Matrix inputs, Matrix labels, double lr, double n)
{
	int	len;
	vector<Matrix>	delta_w;
	vector<Matrix>	delta_b;
	Matrix			delta;
	Matrix			sp;

	len = this->size - 1;
	delta = this->layer[len].activation.sub(labels);
	sp = this->layer[len].beforActivation;
	sp.map(&sigmoidPrim);
	delta = delta.mult(sp);
	delta_b.push_back(delta);
	delta_w.push_back(delta.mult((layer[len - 1].activation).transpose()));
	for (int i = len - 1 ; i >= 0; i--)
	{
		sp = this->layer[i].beforActivation;
		sp.map(&sigmoidPrim);
		delta = this->layer[i + 1].weight.transpose().mult(delta);
		delta = delta.prod(sp);
		delta_b.push_back(delta);
		if (i - 1 >= 0)
			delta_w.push_back(delta.mult((layer[i - 1].activation).transpose()));
		else
			delta_w.push_back(delta.mult((inputs).transpose()));
	}
	for (int i = 0; i < this->size; i++)
	{
		delta_w[this->size - 1 - i].scale(lr / n);
		delta_b[this->size - 1 - i].scale(lr / n);
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

void	Network::sgd(struct Data* training_data, int epochs, int mini_batch_size, double lr, struct Data* test_data = NULL)
{
	struct Data *training;
	struct Data	*test;
	int		test_size;
	int		good;
	Matrix	res;

	if (test_data)
		test_size = len_data(test_data);
	training = training_data;
	for (int j = 1; j <= epochs; j++)
	{
		good = 0;
		test = test_data;
		for (int i = 0; training && i < mini_batch_size; i++)
		{
			this->backPropagation(training->input, training->label, lr, mini_batch_size);
			training = training->next;
		}
		while (test)
		{
			res = this->feedForward(test->input);
			if (get_index(test->label) == get_index(res))
				good++;
			test = test->next;
		}
		cout << "Epoch " << j << " : {" << good << " / " << test_size << "}.\n";
	}
}
/*
void	Network::train(Matrix inputs, Matrix targets, double lr, int mini_batch_size)
{
	Matrix	hidden_1; // layer 1 output;
	Matrix	hidden_2; // layer 2 output;
	Matrix	out; // final output
	Matrix	tmphidden_1; // to store the value befor mapping;
	Matrix	tmphidden_2; // to store the value befor mapping;
	Matrix	tmpout; // to store the value befor mapping;

	//Layer 1:
	hidden_1 = this->hidden_1_w.mult(inputs); // i * h1w
	hidden_1 = hidden_1.add(this->hidden_1_b); // i * h1w + h1b
	hidden_1.map(&relu); // relu(i * h1w + h1b)
	//layer 2 :
	hidden_2 = this->hidden_2_w.mult(hidden_1); // h1 * h2w
	hidden_2 = hidden_2.add(this->hidden_2_b); // h1 * h2w + h2b
	hidden_2.map(&sigmoid); //  sigmoid (h1 * h2w + h2b)
	//final output :
	out = this->out_w.mult(hidden_2); // h2 * ow
	out = out.add(this->out_b); // h2 * ow + ob
	softmax(&(out)); // softmax(h2 * ow + ob)

}*/
