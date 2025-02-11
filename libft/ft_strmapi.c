/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:58:44 by olomova           #+#    #+#             */
/*   Updated: 2024/02/16 19:02:49 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	leng(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		len;
	unsigned int		i;
	char				*p;

	len = leng(s);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
/*char fun(unsigned int i, char c)
{
        c = c + i;
        return (c);
}
int main ()
{
	char (*f)(unsigned int, char);
	f = fun;
	printf("%s\n", ft_strmapi("ABC", f));
}*/
