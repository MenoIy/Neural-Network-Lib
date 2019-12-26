/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:21:51 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/26 19:50:27 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nnl.h"

int main()
{
	t_network	*net;
	t_matrix	*in;

	in = new_matrix(1, 2);
	matrix_randomize(in);

	net = new_network(2, 2, 1);


	print_matrix(net->hidden_bias);
	print_matrix(net->hidden_weight);
	print_matrix(net->out_bias);
	print_matrix(net->out_weight);
	t_matrix	*out;

	out = feedforward(net, in);
	print_matrix(out);
	del_network(&net);
	return (0);
}
