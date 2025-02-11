/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:18:20 by olomova           #+#    #+#             */
/*   Updated: 2024/02/17 14:19:02 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s01;
	char	*s02;

	i = 0;
	s01 = (char *)s1;
	s02 = (char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if ((unsigned char)s01[i] > (unsigned char)s02[i])
		{
			return (1);
		}
		else if ((unsigned char)s01[i] < (unsigned char)s02[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
