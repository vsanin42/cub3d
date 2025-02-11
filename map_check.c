/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025-02-09 19:09:29 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	is_out_of_bounds(char **map, int x, int y, int rows)
{
	return (x < 0 || y < 0 || x >= rows
		|| y >= (int)ft_strlen(map[x]) || map[x][y] == ' ');
}

int	flood_fill(t_map_data *data, int x, int y)
{
	if (is_out_of_bounds(data->map, x, y, data->rows)
		|| data->map[x][y] == '1' || data->visited[x][y])
		return (1);
	data->visited[x][y] = 1;
	if (data->map[x][y] == '0' || data->map[x][y] == 'N'
		|| data->map[x][y] == 'S' || data->map[x][y] == 'E'
		|| data->map[x][y] == 'W')
	{
		if (is_out_of_bounds(data->map, x - 1, y, data->rows)
			|| is_out_of_bounds(data->map, x + 1, y, data->rows)
			|| is_out_of_bounds(data->map, x, y - 1, data->rows)
			|| is_out_of_bounds(data->map, x, y + 1, data->rows))
		{
			return (0);
		}
	}
	return (flood_fill(data, x - 1, y)
		&& flood_fill(data, x + 1, y)
		&& flood_fill(data, x, y - 1)
		&& flood_fill(data, x, y + 1));
}

t_map_data	*init_map_data(char **map, int rows)
{
	int			i;
	t_map_data	*data;

	data = malloc(sizeof(t_map_data));
	if (!data)
		return (NULL);
	data->map = map;
	data->rows = rows;
	data->visited = (int **)malloc(rows * sizeof(int *));
	if (!data->visited)
	{
		free(data);
		return (NULL);
	}
	i = -1;
	while (++i < rows)
	{
		data->visited[i] = (int *)ft_calloc(ft_strlen(map[i]) + 1, sizeof(int));
		if (!data->visited[i])
		{
			free_map_data(data);
			return (NULL);
		}
	}
	return (data);
}

void	free_map_data(t_map_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		while (i < data->rows)
		{
			free(data->visited[i]);
			i++;
		}
		free(data->visited);
		free(data);
	}
}

int	check_player(char **grid)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'S' || grid[i][j] == 'W'
				|| grid[i][j] == 'N' || grid[i][j] == 'E')
				flag++;
			j++;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}
