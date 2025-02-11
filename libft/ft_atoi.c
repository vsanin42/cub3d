/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 12:28:08 by olomova           #+#    #+#             */
/*   Updated: 2024/02/18 12:28:12 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c)
{
	if (c == 0 || c == 9 || c == 10 || c == 11 || c == 12 || c == 13)
	{
		return (1);
	}
	return (0);
}

static int	convert_int(const char *s)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (s[i] != '\0' && s[i] <= '9' && s[i] >= '0')
	{
		res = res * 10;
		res = res + s[i] - '0';
		i++;
	}
	return (res);
}

static int	ft_atoi_cut(const char *s, int minus)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (s[i] == '+')
	{
		i++;
	}
	else if (s[i] == '-')
	{
		i++;
		minus = -1;
	}
	if (s[i] >= '0' && s[i] <= '9')
	{
		res = convert_int(&s[i]);
	}
	return (res * minus);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;

	i = 0;
	minus = 1;
	while (check(str[i]) == 1)
	{
		i++;
	}
	if (ft_strncmp("-2147483648", str, 12) == 0)
	{
		return (-2147483648);
	}
	return (ft_atoi_cut(&str[i], minus));
}
/*int	main()
{
	printf("%d\n", ft_atoi("-+42"));
	printf("%d\n", ft_atoi("-\n\n\t42"));
}*/
