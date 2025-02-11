/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:34:56 by olomova           #+#    #+#             */
/*   Updated: 2024/02/18 12:59:45 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*cut_substr(void)
{
	char	*res;

	res = malloc(sizeof(char));
	if (res == NULL)
		return (res);
	res[0] = '\0';
	return (res);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		return (cut_substr());
	}
	else
	{
		if (start + len > ft_strlen(s))
			len = ft_strlen(s) - start;
		res = malloc(sizeof(char) * (len + 1));
		if (res == NULL)
			return (NULL);
		i = 0;
		while (++i - 1 < len)
			*(res + i - 1) = *(s + start + i - 1);
		*(res + i - 1) = '\0';
		return (res);
	}
}
