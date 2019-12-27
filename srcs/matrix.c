/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 15:28:11 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/26 21:16:54 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nnl.h"

void		print_matrix(t_matrix *matrix)
{
	printf("Matrix with %zu cols and %zu row\n", matrix->col, matrix->row);
	for (int i = 0; i < matrix->row; i++)
	{
		for (int j = 0; j < matrix->col; j++)
		{
			printf("| %.2lf ", matrix->tab[i][j]);
		}
		printf("\n");
	}
}

void		del_matrix(t_matrix **matrix)
{
	t_matrix	*todel;

	todel = *matrix;
	for (int i = 0; todel->tab[i]; i++)
	{
		free(todel->tab[i]);
		todel->tab[i] = NULL;
	}
	free(todel->tab);
	todel->tab = NULL;
	free(todel);
	todel = NULL;
}

t_matrix	*matrix_cpy(t_matrix *a)
{
	t_matrix	*new;

	if (!(new = new_matrix(a->col, a->row)))
		return NULL;
	for (int i = 0; i < a->row; i++)
	{
		for (int j = 0; j < a->col; j++)
		{
			new->tab[i][j] = a->tab[i][j];
		}
	}
	return new;
}

void	matrix_randomize(t_matrix	*matrix)
{
	srand ( time ( NULL));

	for (int i = 0; i < matrix->row; i++)
	{
		for (int j = 0; j < matrix->col; j++)
		{
			matrix->tab[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0;
		}
	}
}

t_matrix 	*new_matrix(size_t col, size_t row)
{
	t_matrix	*matrix;

	if (!(matrix = (t_matrix *)memalloc(sizeof(t_matrix *))))
	{
		dprintf(2, "Error allocating memory in new_matrix\n");
		return (NULL);
	}
	matrix->col = col;
	matrix->row = row;
	if (!(matrix->tab = (double **)memalloc(sizeof(double **) * (row + 1))))
	{
		dprintf(2, "Error allocating memory in new_matrix\n");
		del_matrix(&matrix);
		return (NULL);
	}
	for (int i = 0; i < row; i++)
	{
		if (!(matrix->tab[i] = (double *)memalloc(sizeof(double *) * (col + 1))))
		{
			dprintf(2, "Error allocating memory in new_matrix\n");
			del_matrix(&matrix);
			return (NULL);
		}
	}
	return (matrix);
}
