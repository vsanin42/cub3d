/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/14 18:00:51 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_out_of_bounds(char **map, int x, int y, int rows)
{
	return (x < 0 || y < 0 || x >= rows
		|| y >= ft_strlen(map[x]) || map[x][y] == ' ');
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
		data->visited[i] = (int *)ft_calloc(ft_strlen(map[i]) + 1, sizeof(int)); // why + 1?
		if (!data->visited[i])
		{
			free_map_data(data, i); // pass index up to which we want to free rows to avoid freeing unallocated rows
			return (NULL);
		}
	}
	return (data);
}

// 1. default: index == -1. stop index == rows. free all visited[i]
// 2. if failed at initializing of visited array: index == last valid index.
// stop index == index to stop at. free up to that index only.
void	free_map_data(t_map_data *data, int index)
{
	int	i;
	int	stop_index;

	i = 0;
	if (!data)
		return ;
	stop_index = data->rows;		
	if (index > -1)
		stop_index = index;
	while (i < stop_index)
	{
		free(data->visited[i]);
		i++;
	}
	free(data->visited);
	free(data);
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
	return (err("Error: Missing/extra player position!"), 0);
}
