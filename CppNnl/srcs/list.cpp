/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 22:47:35 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/27 23:32:01 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"

void	data_push(struct Data **head, Matrix label, Matrix input)
{
	struct Data* newData = new Data;

	newData->label = label;
	newData->input = input;
	newData->next = *head;
	*head = newData;
}
