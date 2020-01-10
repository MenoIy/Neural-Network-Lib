#include "network.hpp"

Matrix	Network::feedForward_v2(Matrix	inputs)
{
	Matrix	in;

	in = inputs;
	for (int i = 0; i < this->size; i++){
		this->layer[i].activation = this->layer[i].weight.mult(in);
		this->layer[i].activation = this->layer[i].activation.add(this->layer[i].bias);
		this->layer[i].beforActivation = this->layer[i].activation.clone();
		if (i == this->size - 2)
			this->layer[i].activation.map(&sigmoid);
		else if (i == this->size - 1)
			softmax(&(this->layer[i].activation));
		else
			this->layer[i].activation.map(&leakyRelu);
		in  = this->layer[i].activation;
	}
	return (in);
}

void	Network::backPropagation_v2(Matrix inputs, Matrix labels, double lr, double n)
{
	int	len;
	vector<Matrix>	delta_w;
	vector<Matrix>	delta_b;
	Matrix			delta;
	Matrix			sp;
	Matrix			out;

	len = this->size - 1;
	out = this->feedForward_v2(inputs);
	delta = crossEntropyPrim(out, labels);
	sp = this->layer[len].beforActivation;
	sp = softmaxPrim(sp);
	delta = delta.prod(sp);
	delta_b.push_back(delta);
	delta_w.push_back(delta.mult((layer[len - 1].activation).transpose()));
	for (int i = len - 1; i >= 0; i--)
	{
		sp = this->layer[i].beforActivation.clone();
		if (i == len - 1)
			sp.map(&sigmoidPrim);
		else
			sp.map(&leakyReluPrim);
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

void	Network::sgd_v2(struct Data* training_data, int epochs, int mini_batch_size, double lr, struct Data* test_data = NULL)
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
			this->backPropagation_v2(training->input, training->label, lr, mini_batch_size);
			training = training->next;
		}
		while (test)
		{
			res = this->feedForward_v2(test->input);
			if (get_index(test->label) == get_index(res))
				good++;
			test = test->next;
		}
		cout << "Epoch " << j << " : {" << good << " / " << test_size << "}.\n";
	}
}
