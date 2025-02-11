/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:56:15 by olomova           #+#    #+#             */
/*   Updated: 2024/02/17 18:43:22 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*p;

	if (element_size > 4294967295 && num_elements > 4294967295)
	{
		return (NULL);
	}
	p = (void *)malloc(num_elements * element_size);
	if (!p)
	{
		return (NULL);
	}
	else
	{
		ft_memset(p, 0, element_size * num_elements);
	}
	return (p);
}
