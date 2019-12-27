/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_network.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:37:59 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/27 18:31:17 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nnl.h"

void		del_network(t_network **net)
{
	t_network	*todel;

	todel = *net;
	del_matrix(&(todel->hidden_weight));
	del_matrix(&(todel->hidden_bias));
	del_matrix(&(todel->out_bias));
	del_matrix(&(todel->out_weight));
	free(*net);
	*net = NULL;
}

t_network	*new_network(int in, int hidden, int out, double lr)
{
	t_network	*net;

	if (!(net = (t_network*)memalloc(sizeof(t_network *))))
	{
		del_network(&net);
		dprintf(2, "Error allocating memory in new_network");
		return NULL;
	}
	net->in_count = in;
	net->hidden_count = hidden;
	net->out_count = out;
	net->lr = lr;
	if (!(net->hidden_weight = new_matrix(in, hidden)))
	{
		del_network(&net);
		dprintf(2, "Error allocating memory in new_network");
		return NULL;
	}
	if (!(net->hidden_bias = new_matrix(1, hidden)))
	{
		del_network(&net);
		dprintf(2, "Error allocating memory in new_network");
		return NULL;
	}
	if (!(net->out_weight = new_matrix(hidden, out)))
	{
		del_network(&net);
		dprintf(2, "Error allocating memory in new_network");
		return NULL;
	}
	if (!(net->out_bias = new_matrix(1, out)))
	{
		del_network(&net);
		dprintf(2, "Error allocating memory in new_network");
		return NULL;
	}
	matrix_randomize(net->hidden_weight);
	matrix_randomize(net->hidden_bias);
	matrix_randomize(net->out_weight);
	matrix_randomize(net->out_bias);

	return (net);	
}
