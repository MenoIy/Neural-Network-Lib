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
	return (1.0 / (1.0  - x));
}

double	relu(double x)
{
	return (x  > 0.0 ? x : 0.0);
}

double	sigmoidPrim(double x)
{
	double	z;
	z = sigmoid(x);
	return (z * (1.0 - z));
}
static double	reluPrim(double x)
{
	return (x > 0.0 ? 1.0 : 0.0);
}


/*
double	sigmoid(double x)
{
	return (1.0 / (1.0 + exp(-x)));
}

static double dsigmoid(double x)
{
	return (x * (1.0 - x));
}

static double	relu(double x)
{
	return (x > 0.0 ? x : 0.0);
}


static void softmax(Matrix *t)
{
	double	sum = 0;

	for (int i = 0; i < t->row; i++)	{
		sum += exp(t->tab[i][0]);
	}
	for (int i = 0; i < t->row; i++)	{
		t->tab[i][0] = exp(t->tab[i][0]) / sum;
	}
}

Matrix	Network::feedForward(Matrix	inputs)
{
	Matrix	hidden_1; // layer 1 output;
	Matrix	hidden_2; // layer 2 output;
	Matrix	out; // final output

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
	return out;
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

void	Network::sgd(struct Data* training_data,
		int epochs, int mini_batch_size, double lr, struct Data* test_data = NULL)
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
			this->train(training->input, training->label, lr, mini_batch_size);
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
