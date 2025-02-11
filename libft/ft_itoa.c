/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:53:56 by olomova           #+#    #+#             */
/*   Updated: 2024/02/17 18:02:50 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	symbols(int n, int len, char *p, int j);

static int	leng(int n)
{
	int	len;
	int	minus;

	len = 1;
	minus = 0;
	if (n < 0)
	{
		minus++;
		n = -n;
	}
	while (n > 9)
	{
		len++;
		n = n / 10;
	}
	return (minus + len);
}

static int	poww(int len)
{
	int	i;
	int	ten;

	i = 1;
	ten = 1;
	if (len == 1)
		return (1);
	while (i < len)
	{
		ten = ten * 10;
		i++;
	}
	return (ten);
}

char	*ft_itoa(int n)
{
	int		len;
	int		j;
	char	*p;

	len = leng(n);
	j = len;
	if (n == -2147483647 - 1)
	{
		return (ft_strdup("-2147483648\0"));
	}
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
	{
		return (NULL);
	}
	symbols(n, len, p, j);
	return (p);
}

static void	symbols(int n, int len, char *p, int j)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		len--;
		n = -n;
		p[i] = '-';
		i++;
	}
	while (i < j)
	{
		p[i] = n / poww(len) + '0';
		n = n % poww(len);
		i++;
		len--;
	}
	p[i] = '\0';
}
/*int main(void)
{
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1000));
	printf("%s\n", ft_itoa(-2147483647));
	printf("%s\n", ft_itoa(-1000));
	printf("%s\n", ft_itoa(-2147483648));
}*/
