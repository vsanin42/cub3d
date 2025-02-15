/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/15 16:26:30 by vsanin           ###   ########.fr       */
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

// if NSWE was found:
// 1. set the coordinates x and y based on j and i.
// 2. set the orientation based on NSWE.
// dir and plane are set to 0 in alloc_all, so we just replace what's needed.
// 3. set plane.x and plane.t PERPENDICULAR to dir.
// 4. 0.66 dictates field of view, sign changes to reflect the right side.
// example: for direction WEST (-1, 0), right hand side is NORTH
// so adding the vector plane and getting farthest right ray means adding -0.66 to y dimension
// this is crazy
// left (x = -1) ------ 0 ------- right (x = 1)
// up (y = -1) -------- 0 ------- down (y = 1) (O_o)
// !!!!! 
// IF DIRECTIONS AND EVERYTHING IS FLIPPED OR SOMETHING THEN FLIP SIGNS OF 0.66 VALUES !!!!!
void	set_start_pos(char c, int i, int j, t_game *game)
{
	game->pos.x = j; // x = column from left to right = j
	game->pos.y = i; // y = row from top to bottom = i
	if (c == 'N') // dir: (0, -1); plane: (0.66, 0)
	{
		game->dir.y = -1;
		game->plane.x = 0.66;
	}
	else if (c == 'S') // dir: (0, 1); plane: (-0.66, 0)
	{
		game->dir.y = 1;
		game->plane.x = -0.66;
	}
	else if (c == 'W') // dir: (-1, 0); plane: (0, -0.66)
	{
		game->dir.x = -1;
		game->plane.y = -0.66;
	}
	else if (c == 'E') // dir: (1, 0); plane: (0, 0.66)
	{
		game->dir.x = 1;
		game->plane.y = 0.66;
	}
}

int	check_player(char **grid, t_game *game)
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
			{
				set_start_pos(grid[i][j], i, j, game);
				flag++;
			}
			j++;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (err("Error: Missing/extra player position!"), 0);
}
