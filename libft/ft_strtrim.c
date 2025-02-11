/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:51:49 by olomova           #+#    #+#             */
/*   Updated: 2024/02/18 14:35:06 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*allocate_and_copy_trimmed(const char *s1, int start, int end)
{
	int		i;
	int		trimmed_len;
	char	*trimmed;

	trimmed_len = end - start + 1;
	i = 0;
	trimmed = (char *)malloc((trimmed_len + 1) * sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	while (i < trimmed_len)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	trimmed[trimmed_len] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= 0 && is_in_set(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	return (allocate_and_copy_trimmed(s1, start, end));
}
/*int main(int argc, char *argv[])
{
	if (argc > 0)
	printf("%s\n", ft_strtrim(argv[1], argv[2]));
}*/
