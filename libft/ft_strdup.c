/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:58:27 by olomova           #+#    #+#             */
/*   Updated: 2024/02/16 16:02:46 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		j;
	char	*dub;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	dub = (char *)malloc((i + 1) * sizeof(char));
	if (!dub)
	{
		return (NULL);
	}
	while (j < i)
	{
		dub[j] = str[j];
		j++;
	}
	dub[j] = '\0';
	return (dub);
}
