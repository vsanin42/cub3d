/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/09 22:00:55 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	return (i);
}

int	edit_paths(char **textures)
{
	int	i;
	int	len;

	i = 0;
	if (!textures)
		return (0);
	while (textures[i])
	{
		trim_spaces(textures[i]);
		len = ft_strlen(textures[i]);
		if (len < 5 || textures[i][len - 1] != 'm'
			|| textures[i][len - 2] != 'p' || textures[i][len - 3] != 'x'
			|| textures[i][len - 4] != '.')
			return (0);
		i++;
	}
	return (1);
}
