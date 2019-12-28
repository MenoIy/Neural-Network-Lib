/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 22:47:35 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/28 17:17:50 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"

void	push_data(struct Data **head, Matrix label, Matrix input)
{
	struct Data *newData = new Data;
   
	newData->label = label;
	newData->input = input;
	newData->next = *head;
	*head = newData;
}

void	del_data(struct Data **head)
{
	struct Data *tmp;
	struct Data *curr;

	curr = *head;
	while (curr != NULL)
	{
		tmp = curr->next;
		delete(curr);
		curr = tmp;
	}
	*head = NULL;
}

int		len_data(struct Data *head)
{
	struct Data *tmp;
	int	i = 0;

	tmp = head;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
