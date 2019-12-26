/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:31:44 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/26 19:42:37 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NNL_H
#define NNL_H

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

typedef	struct	s_matrix
{
	size_t	row;
	size_t	col;
	double	**tab;
}				t_matrix;

typedef struct	s_network
{
	int			in_count;
	int 		hidden_count;
	int 		out_count;
	t_matrix	*hidden_weight;
	t_matrix	*hidden_bias;
	t_matrix	*out_weight;
	t_matrix	*out_bias;
}				t_network;




t_matrix	*new_matrix(size_t col, size_t row);
void		del_matrix(t_matrix **matrix);
void		print_matrix(t_matrix *matrix);
void		matrix_randomize(t_matrix *matrix);
void		matrix_add(t_matrix *matrix, t_matrix *to_add, double value);
t_matrix	*matrix_mult(t_matrix *a, t_matrix *b);
void		matrix_scale(t_matrix *matrix, double value);
t_matrix	*matrix_transpose(t_matrix *matrix);
void		matrix_map(t_matrix *matrix, double(*f)(double value));




t_matrix	*feedforward(t_network *net, t_matrix *in);
t_network	*new_network(int in , int hidden, int out);
void		del_network(t_network **network);

void		*memalloc(size_t size);

#endif
