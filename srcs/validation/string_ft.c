/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:22:31 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/19 12:51:49 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		err("Error: Texture not specified!");
	return (res);
}

int	check_texture_path(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (check_fd(fd) == -1)
		return (0);
	close(fd);
	return (1);
}

// first check inside while loop: if only whitespaces (empty texture path)
// OR if malloc failed
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
			return (0);
		len = ft_strlen(textures[i]);
		if (len < 5 || textures[i][len - 1] != 'm'
			|| textures[i][len - 2] != 'p' || textures[i][len - 3] != 'x'
			|| textures[i][len - 4] != '.')
			return (err("Error: Wrong texture format!"), 0);
		if (!check_texture_path(textures[i]))
			return (err("Error: Opening .xpm failed!"), 0);
		i++;
	}
	return (1);
}

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
