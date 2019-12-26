/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 19:33:28 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/26 19:52:02 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nnl.h"

double	sigmoid(double x)
{
	double res;

	res = 1 / (1 + exp(- x));
	return (res);
}

t_matrix	*feedforward(t_network *net, t_matrix *in)
{
	t_matrix	*hidden;
	t_matrix	*out;

	if (!(hidden = matrix_mult(net->hidden_weight , in)))
		return NULL;
	matrix_add(hidden, net->hidden_bias, 0);
	matrix_map(hidden, &sigmoid);

	if (!(out = matrix_mult(net->out_weight , hidden)))
	{
		del_matrix(&hidden);
		return NULL;
	}
	matrix_add(out, net->out_bias, 0);
	matrix_map(out, &sigmoid);
	del_matrix(&hidden);
	return (out);
}
