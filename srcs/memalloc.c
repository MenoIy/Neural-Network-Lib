/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:26:30 by kdaou             #+#    #+#             */
/*   Updated: 2019/12/26 15:26:18 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "nnl.h"

void	*memalloc(size_t size)
{
	void	*ptr;

	ptr = 0;
	if (!(ptr = (void *)malloc(sizeof(size_t) * size)))
		return (NULL);
	bzero(ptr, size);
	return (ptr);
}
