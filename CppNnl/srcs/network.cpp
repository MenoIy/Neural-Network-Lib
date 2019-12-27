/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:31:28 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/27 22:39:40 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "network.hpp"

void	Network::print()
{
	this->hiddenWeight.print();
	this->hiddenBias.print();
	this->outWeight.print();
	this->outBias.print();
}

double	sigmoid(double x)
{
	return (1 / (1 + exp(-x)));
}

static double dsigmoid(double x)
{
	return (x * (1 - x));
}

Matrix	Network::feedForward(Matrix	input)
{
	Matrix	hidden;
	Matrix	out;

	hidden = this->hiddenWeight.mult(input);
	hidden = hidden.add(this->hiddenBias);
	hidden.map(&sigmoid);

	out = this->outWeight.mult(hidden);
	out = out.add(this->outBias);
	out.map(&sigmoid);
	return (out);
}

void	Network::train(Matrix inputs, Matrix targets, double lr = 0.1)
{
	Matrix	hidden;
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

	/* feedForward*/
	hidden = this->hiddenWeight.mult(input);
	hidden = hidden.add(this->hiddenBias);
	hidden.map(&sigmoid);

	out = this->outWeight.mult(hidden);
	out = out.add(this->outBias);
	out.map(&sigmoid);
	/*calcule errors*/
	out_errors = targets.sub(out);

	/*hidden to out gradient*/
	
	out_gradient = out.clone(); // clone
	out_gradient.map(&dsigmoid);
	out_gradient = out.mult(out_errors);
	out_gradient.scale(lr);

	/*calcule hidden to out deltas*/

	hidden_t = hidden.transpose(); 
	delta_hidden_out_weights = out_gradient.mult(hidden_t);
	this->outWeight = this->outWeight.add(delta_hidden_out_weights) ;
	this->outBias = this->outBias.add(out_gradient);

	/*hidden errors*/
	hidden_out_t = this->outWeight.transpose();
	hidden_errors = hidden_out_t.mult(out_errors);

	/*inpute to hidden gradient*/
	hidden_gradient = hidden.clone(); // clone
	hidden_gradient.map(&dsigmoid);
	hidden_gradient.mult(hidden_errors);
	hidden_gradient.scale(lr);

	/*calcule input to hidden deltas*/
	inputs_t = inputs.transpose();
	delta_input_hidden_weights = hidden_gradient.mult(inputs_t);
	this->hiddenWeight = this->hiddenWeight.add(delta_input_hidden_weights);
	this->hiddenBias = this->hiddenBias.add(hidden_gradient);
}
