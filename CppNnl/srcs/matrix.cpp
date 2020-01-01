/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 16:06:47 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/31 23:46:09 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.hpp"

void	Matrix::shape()
{
	cout << "{ " << this->row << " , " << this->col << " }" << "\n";
}

void	Matrix::print()
{
	cout << std::setprecision(2) << std::fixed;
	cout << "------" << this->row << " x " << this->col << "------" << "\n";
	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			cout << this->tab[i][j] << " "; 
		}
		cout << '\n';
	}
	cout << '\n';
}

void	Matrix::randomize()
{
	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			this->tab[i][j] = ((double) rand() / (RAND_MAX)) * 2 - 1 ;
		}
	}
}

void	Matrix::scale(double value)
{
	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			this->tab[i][j] *= value;
		}
	}
}

void	Matrix::map(double (*f)(double value))
{
	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			this->tab[i][j] = (*f)(this->tab[i][j]);
		}
	}
}

Matrix	Matrix::add(Matrix to_add)
{
	Matrix ret(this->row, this->col);

	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			ret.tab[i][j] = this->tab[i][j] + to_add.tab[i][j];
		}
	}
	return (ret);
}

Matrix	Matrix::sub(Matrix to_sub)
{
	Matrix ret(this->row, this->col);

	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			ret.tab[i][j] = this->tab[i][j] - to_sub.tab[i][j];
		}
	}
	return (ret);
}

Matrix	Matrix::transpose()
{
	Matrix ret(this->col, this->row);

	for (int i = 0; i < ret.row; i++) { 
		for (int j = 0; j < ret.col; j++){ 
			ret.tab[i][j] = this->tab[j][i];
		}
	}
	return (ret);
}

Matrix	Matrix::mult(Matrix to_mult)
{
	Matrix ret(this->row, to_mult.col);
	double	sum;

	for (int i = 0; i < ret.row; i++) { 
		for (int j = 0; j < ret.col; j++){
			sum = 0;
			for (int k = 0; k < this->col; k++){
				sum += this->tab[i][k] * to_mult.tab[k][j];
			}
			ret.tab[i][j] = sum;
		}
	}
	return (ret);
}

Matrix	Matrix::clone()
{
	Matrix ret(this->row, this->col);

	for (int i = 0; i < this->row; i++) { 
		for (int j = 0; j < this->col; j++){ 
			ret.tab[i][j] = this->tab[i][j];
		}
	}
	return (ret);
}

Matrix	Matrix::prod(Matrix	to_prod)
{	
	Matrix ret(this->row, this->col);

	for (int i = 0; i < this->row; i++){
		for (int j = 0; j < this->col; j++){
			ret.tab[i][j] = this->tab[i][j] * to_prod.tab[i][0];
		}
	}
	return (ret);
}
