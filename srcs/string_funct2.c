/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/13 21:10:04 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	return (i);
}

// wrapper for ft_strtrim function.
// 1. trims whitespaces of a string, returns it in the end
// 2. frees old string
// 3. if trim returned null, malloc failed inside
// 4. if trim returned empty string, it means it's whitespaces only
// -> start == end, nothing to be copied to res but \0 -> empty string
char	*trim_wrapper(char *str)
{
	char	*res;

	res = ft_strtrim(str, " \t\n\v\f\r");
	free(str);
	if (res == NULL)
		err("Error: ft_strtrim malloc failed!");
	else if (*res == '\0')
		err("Error: texture not specified!");
	return (res);
}

// replaced trim_spaces with ft_strtrim
int	edit_paths(char **textures)
{
	int	i;
	int	len;

	i = 0;
	if (!textures)
		return (0);
	while (textures[i])
	{
		textures[i] = trim_wrapper(textures[i]);
		if (!textures[i] || *textures[i] == '\0')
			return (0); // if only whitespaces = empty texture path / if malloc failed
		len = ft_strlen(textures[i]);
		if (len < 5 || textures[i][len - 1] != 'm'
			|| textures[i][len - 2] != 'p' || textures[i][len - 3] != 'x'
			|| textures[i][len - 4] != '.')
			return (err("Error: wrong texture format!"), 0);
		i++;
	}
	return (1);
}
