/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:22:32 by kdaou             #+#    #+#             */
/*   Updated: 2020/01/03 19:36:06 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP
#include <pthread.h> 
# include "matrix.hpp"
# define EPSILON 0.0000000000001
#include "list.hpp"


class Layer
{
	public :
		Matrix	weight;
		Matrix	bias;
		Matrix	activation;
		Matrix	beforActivation;

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
		Matrix	feedForward_v1(Matrix input);
		void	backPropagation_v1(Matrix inputs, Matrix labels, double lr, double n);
		void	sgd_v1(struct Data* training_data, int epochs, int mini_batch_size, double lr, struct Data* test_data);
		Matrix	feedForward_v2(Matrix input);
		void	backPropagation_v2(Matrix inputs, Matrix labels, double lr, double n);
		void	sgd_v2(struct Data* training_data, int epochs, int mini_batch_size, double lr, struct Data* test_data);
		double	crossEntropy(Matrix	out, Matrix label);
		double	getError(Matrix out, Matrix label);
		void	shape();
		void	print();

};

double			sigmoid(double x);
double			relu(double x);
double			sigmoidPrim(double x);
double			reluPrim(double x);
void			softmax(Matrix *s);
double			leakyRelu(double x);
double 			leakyReluPrim(double x);
Matrix			softmaxPrim(Matrix s);
Matrix	crossEntropyPrim(Matrix	out, Matrix label);

# endif
