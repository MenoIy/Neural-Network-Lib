/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 16:09:24 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/27 17:11:33 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nnl.h"

void	matrix_sub(t_matrix	*matrix, t_matrix *to_sub, double value)
{
	for (int i = 0; matrix->tab[i]; i++)
	{
		for (int j = 0; j <  matrix->col; j++)
		{
			if (to_sub)
				matrix->tab[i][j] -= to_sub->tab[i][j];
			else
				matrix->tab[i][j] -= value;
		}
	}
}

void	matrix_add(t_matrix	*matrix, t_matrix *to_add, double value)
{
	for (int i = 0; matrix->tab[i]; i++)
	{
		for (int j = 0; j <  matrix->col; j++)
		{
			if (to_add)
				matrix->tab[i][j] += to_add->tab[i][j];
			else
				matrix->tab[i][j] += value;
		}
	}
}

void	matrix_scale(t_matrix *matrix, double value)
{
	for (int i = 0; i < matrix->row; i++)
	{
		for (int j = 0; j <  matrix->col; j++)
		{
			matrix->tab[i][j] *= value;
		}
	}
}

t_matrix	*matrix_mult(t_matrix *a, t_matrix *b)
{
	t_matrix	*res;
	double		sum;

	sum = 0;
	if (a->col != b->row)
	{
		dprintf(2, "Error columns of a must match row of b\n");
		return NULL;
	}
	if (!(res = new_matrix(b->col , a->row)))
	{
		dprintf(2, "Error allocating memory in matrix_mult\n");
		return NULL;
	}
	for (int i = 0; i < res->row; i++)
	{
		for (int j = 0; j < res->col; j++)
		{
			sum = 0;
			for (int k = 0; k < a->col; k++)
			{
				sum += a->tab[i][k] * b->tab[k][j];
			}
			res->tab[i][j] = sum;
		}
	}
	return (res);
}

t_matrix	*matrix_transpose(t_matrix	*matrix)
{
	t_matrix	*res;

	if (!(res = new_matrix(matrix->row , matrix->col)))
	{
		dprintf(2, "Error allocating memory in matrix_tranpose\n");
		return NULL;
	}
	for (int i = 0; i < res->row; i++)
	{
		for (int j = 0; j < res->col; j++)
		{
			res->tab[i][j] = matrix->tab[j][i];
		}
	}
	return res;
}

void	matrix_map(t_matrix *matrix, double (*f)(double value))
{
	for (int i = 0; i < matrix->row; i++)
	{
		for (int j = 0; j <  matrix->col; j++)
		{
			matrix->tab[i][j] = (*f)(matrix->tab[i][j]);
		}
	}
}
