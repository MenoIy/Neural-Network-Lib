/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:21:51 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/26 22:02:45 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nnl.h"

int main()
{
	t_network	*net;
	t_matrix	*in;

	in = new_matrix(1, 3);
	matrix_randomize(in);
	t_matrix *target;
	target = new_matrix(1, 2);

	net = new_network(3, 5, 2, 2.0);

	train(net, in, target);
	del_network(&net);
	return (0);
}
