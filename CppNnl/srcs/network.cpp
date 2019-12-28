#include "network.hpp"

void	Network::print()
{
	this->hiddenWeight.print();
	this->hiddenBias.print();
	this->outWeight.print();
	this->outBias.print();
}

double	sigmoidPrim(double x)
{
	double	z;
	z = sigmoid(x);
	return (z * (1.0 - z));
}

double	sigmoid(double x)
{
	return (1 / (1 + exp(-x)));
}

static double dsigmoid(double x)
{
	return (x * (1 - x));
}



/*
 * FeedForward algorithm : 
 * out =  sigmoid (w * in + b) where w is the weight and 
 * b is the bias and in are the input from the previous layer
 * we is sigmoid to limit the result between (0, 1);
 */
Matrix	Network::feedForward(Matrix	inputs)
{
	Matrix	hiddens;
	Matrix	out;

	hiddens = this->hiddenWeight.mult(inputs);
	hiddens = hiddens.add(this->hiddenBias);
	hiddens.map(&sigmoid);

	out = this->outWeight.mult(hiddens);
	out = out.add(this->outBias);
	out.map(&sigmoid);
	return (out);
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

/*
void	Network::train(Matrix inputs, Matrix targets, double lr, int trr)
{
	Matrix	hiddens;
	Matrix	out;
	Matrix	out_errors;
	Matrix	hidden_out_t;
	Matrix	hidden_errors;
	Matrix	out_gradient;
	Matrix	hidden_gradient;
	Matrix	hidden_t;
	Matrix	inputs_t;
	Matrix	delta_hidden_out_weights;
	Matrix	delta_input_hidden_weights;

	//feedForward
	hiddens = this->hiddenWeight.mult(inputs);
	hiddens = hiddens.add(this->hiddenBias);
	hiddens.map(&sigmoid);

	out = this->outWeight.mult(hiddens);
	out = out.add(this->outBias);
	out.map(&sigmoid);
	//calcule errors
	out_errors = targets.sub(out);

	//hidden to out gradient
	
	out_gradient = out.clone(); // clone
	out_gradient.map(&dsigmoid);
	out_gradient = out.mult(out_errors);
	out_gradient.scale(lr );
	//hidden errors
	hidden_out_t = this->outWeight.transpose();
	hidden_errors = hidden_out_t.mult(out_errors);
	//calcule hidden to out deltas

	hidden_t = hiddens.transpose(); 
	delta_hidden_out_weights = out_gradient.mult(hidden_t);
	this->outWeight = this->outWeight.add(delta_hidden_out_weights) ;
	this->outBias = this->outBias.add(out_gradient);



	//inpute to hidden gradient
	hidden_gradient = hiddens.clone(); // clone
	hidden_gradient.map(&dsigmoid);
	hidden_gradient.mult(hidden_errors);
	hidden_gradient.scale(lr);

	//calcule input to hidden deltas
	inputs_t = inputs.transpose();
	delta_input_hidden_weights = hidden_gradient.mult(inputs_t);
	this->hiddenWeight = this->hiddenWeight.add(delta_input_hidden_weights);
	this->hiddenBias = this->hiddenBias.add(hidden_gradient);
}
*/
void	Network::train(Matrix inputs, Matrix targets, double lr, int mini_batch_size)
{
	Matrix	hiddens;
	Matrix	out;
	Matrix	outErrors;
	Matrix	hiddenErrors;
	Matrix	hiddenWeightDelta;
	Matrix	outWeightDelta;
	Matrix	hiddenBiasDelta;
	Matrix	outBiasDelta;
	Matrix	hiddens_t;
	Matrix	inputs_t;
	Matrix	outWeight_t;


	//feedForward
	hiddens = this->hiddenWeight.mult(inputs);
	hiddens = hiddens.add(this->hiddenBias);
	hiddens.map(&sigmoid);

	out = this->outWeight.mult(hidden);
	out = out.add(this->outBias);
	out.map(&sigmoid);

	//Errors
	outErrors = out.sub(targets);
	outWeight_t = this->outWeight.transpose();
	hiddenErrors = outWeight_t.mult(outErrors);


	//calcule deltas hidden to out;
	hiddens_t = hiddens.transpose();
	out.map(dsigmoid);
	outWeightDelta = outErrors.mult(out);
	outBiasDelta = outWeightDelta.clone();
	outWeightDelta = outWeightDelta.mult(hiddens_t);
	outWeightDelta.scale(lr / mini_batch_size);
	outBiasDelta.scale(lr / mini_batch_size);
	//this->outWeight = this->outWeight.sub(outWeightDelta);
	//this->outBias = this->outBias.sub(outBiasDelta);


	//calcule deltas in to hidden;
	inputs_t = inputs.transpose();
	hiddens.map(dsigmoid);
	hiddenWeightDelta = hiddenErrors.mult(hidden);
	hiddenBiasDelta = hiddenWeightDelta.clone();
	hiddenWeightDelta = hiddenWeightDelta.mult(inputs_t);
	hiddenBiasDelta.scale(lr / mini_batch_size);
	hiddenWeightDelta.scale(lr / mini_batch_size);
	
	this->hiddenWeight = this->hiddenWeight.sub(hiddenWeightDelta);
	this->hiddenBias = this->hiddenBias.sub(hiddenBiasDelta);
	this->outWeight = this->outWeight.sub(outWeightDelta);
	this->outBias = this->outBias.sub(outBiasDelta);
}
