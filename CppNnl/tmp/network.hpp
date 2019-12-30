/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:22:32 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/30 23:45:21 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP
#include <pthread.h> 
# include "matrix.hpp"
//#include "list.hpp"


class Layer
{
	public :
		Matrix	weight;
		Matrix	bias;

		Layer(int row, int col)
		{
			weight = Matrix(row, col);
			bias = Matrix(row, 1);
			weight.randomize();
			bias.randomize();
		}
};

class Network
{
	public :
		int		size;
		vector<Layer> layer;
		
		Network(int inputSize, int hiddenCount, int hiddenSize[], int outputSize)
		{
			int	tmp;

			size = hiddenCount + 1;
			tmp = inputSize;
			for (int i = 0; i <  hiddenCount; i++){
				layer.push_back(Layer(hiddenSize[i], tmp));
				tmp = hiddenSize[i];
			}
			layer.push_back(Layer(outputSize, tmp));
		}
		void	shape();
		void	print();

	//	Matrix	feedForward(Matrix input);
	//	void	train(Matrix inputs, Matrix targets, double lr, int mini_batch_size);
	/*	void	sgd(struct Data *training_data, int epochs, int mini_batch_size,
					double lr, struct Data *test_data);*/

};

double	sigmoid(double x);
double	relu(double x);

/*
class Network
{
	public :
		int		input;
		int		hidden;
		int		output;
		int		hidden1;
		int		hidden2;
		Matrix	hidden_1_w;
		Matrix	hidden_1_b;
		Matrix	hidden_2_w;
		Matrix	hidden_2_b;
		Matrix	out_w;
		Matrix	out_b;
		Matrix	hiddenWeight;
		Matrix	hiddenBias;
		Matrix	outWeight;
		Matrix	outBias;
		double	lr;
	
	//methode
	Network(int in, int hid, int out)
	{
		input = in;
		hidden = hid;
		output = out;
		hidden1 = 30;
		hidden2 = 30;
		hiddenWeight = Matrix(hidden, in);
		hiddenBias = Matrix(hidden, 1);
		outWeight = Matrix(output, hidden);
		outBias = Matrix(output, 1);
		hiddenWeight.randomize();
		hiddenBias.randomize();
		outWeight.randomize();
		outBias.randomize();
		hidden_1_w = Matrix(hidden1, in);
		hidden_1_b = Matrix(hidden1, 1);
		hidden_2_w = Matrix(hidden2, hidden1);
		hidden_2_b = Matrix(hidden2, 1);
		out_w = Matrix(out ,hidden2);
		out_b = Matrix(out, 1);
		hidden_1_w.randomize();
		hidden_1_b.randomize();
		hidden_2_w.randomize();
		hidden_2_b.randomize();
		out_w.randomize();
		out_b.randomize();
	}
	void	print();
d	Matrix	feedForward(Matrix input);
	void	train(Matrix inputs, Matrix targets, double lr, int mini_batch_size);
	void	sgd(struct Data *training_data, int epochs, int mini_batch_size, double lr, struct Data *test_data);

};

double	sigmoid(double x);*/




# endif
