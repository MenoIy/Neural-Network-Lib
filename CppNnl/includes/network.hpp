/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:22:32 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/27 23:17:07 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORK_HPP
# define NETWORK_HPP
# include "matrix.hpp"

class Network
{
	public :
		int		input;
		int		hidden;
		int		output;
		Matrix	hiddenWeight;
		Matrix	hiddenBias;
		Matrix	outWeight;
		Matrix	outBias;
		double	lr;
	
	/*methode*/
	Network(int in, int hid, int out)
	{
		input = in;
		hidden = hid;
		output = out;
		hiddenWeight = Matrix(hidden, in);
		hiddenBias = Matrix(hidden, 1);
		outWeight = Matrix(output, hidden);
		outBias = Matrix(output, 1);
		hiddenWeight.randomize();
		hiddenBias.randomize();
		outWeight.randomize();
		outBias.randomize();
	}
	void	print();
	Matrix	feedForward(Matrix input);
	void	train(Matrix inputs, Matrix tagets, double lr);

};

double	sigmoid(double x);




# endif
