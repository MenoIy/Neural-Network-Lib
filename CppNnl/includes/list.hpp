/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 22:43:47 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/28 17:16:49 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP
#include "matrix.hpp"
#include <cstdlib>
struct Data
{
	Matrix	label;
	Matrix	input;
	struct Data *next;
};

void	push_data(struct Data **head, Matrix label, Matrix input);
void	del_data(struct Data **head);
int		len_data(struct Data *head);

#endif
