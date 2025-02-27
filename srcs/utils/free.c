/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:02:33 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/27 15:07:22 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// 1. map is always allocated in alloc_all(), but keep the first check.
// 2. grid may not be alloced if textures/floor/ceiling is missing.
// in that case only free the map and exit.
// 3. otherwise free each grid line, grid itself and, finally, the map.
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (!map->grid)
		return (free(map));
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

// free the game struct.
// 1. free indivitual texture locations and the array that holds them.
// 2. free floor, ceiling and map info while checking if they exist.
void	free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->textures)
	{
		while (i < 5)
		{
			if (game->textures[i])
				free(game->textures[i]);
			i++;
		}
		free(game->textures);
	}
	if (game->floor_color)
		free(game->floor_color);
	if (game->ceiling_color)
		free(game->ceiling_color);
	if (game->map)
		free_map(game->map);
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
