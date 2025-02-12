/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/12 14:30:24 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup_without_newline(const char *str)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, str, len);
	dup[len] = '\0';
	return (dup);
}

int	add_map_line(t_map *map, const char *line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[map->height] = ft_strdup_without_newline(line);
	if (!new_grid[map->height])
		return (0);
	new_grid[map->height + 1] = NULL;
	free(map->grid);
	map->grid = new_grid;
	map->height++;
	return (1);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	my_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	trim_spaces(char *str)
{
	char	*end;

	while (my_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return ;
	end = str + ft_strlen(str) - 1;
	while (end > str && my_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
}
