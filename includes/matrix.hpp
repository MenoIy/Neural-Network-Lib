/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 15:15:38 by kdaou             #+#    #+#             */
/*   Updated: 2020/01/03 15:54:39 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_HPP
# define MATRIX_HPP
# include <vector>
# include <iostream>
# include <random>
# include <iomanip>


using namespace std; 

class Matrix
{
	public :
		int						row;
		int						col;
		vector<vector<double> >	tab;
	
	/*Methods*/
		Matrix(int rowCount = 1, int colCount = 1)
		{
			row = rowCount;
			col = colCount;
			tab = vector<vector<double> >(rowCount, vector<double>(colCount));
		}
		void	print();
		void	randomize();
		void	scale(double value);
		void	map(double (*f)(double value));
		Matrix	add(Matrix to_add);
		Matrix	sub(Matrix to_add);
		Matrix	transpose();
		Matrix	mult(Matrix to_mult);
		Matrix	prod(Matrix prod);
		Matrix	clone();
		void	shape();
};



#endif
