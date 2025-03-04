/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:02:33 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/04 17:48:09 by vsanin           ###   ########.fr       */
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

// 1. alloc 3 members of game that we need
// 2. if malloc fails, free all 3 (safe thanks to memset)
// 3. if all ok, set all elements to either NULL or 0, also saves lines in main
int	alloc_and_nullify(t_game *game)
{
	int	i;

	i = 0;
	game->textures = malloc(5 * sizeof(char *));
	game->floor_color = malloc(3 * sizeof(int));
	game->ceiling_color = malloc(3 * sizeof(int));
	if (!game->textures || !game->floor_color || !game->ceiling_color)
	{
		free(game->textures);
		free(game->floor_color);
		free(game->ceiling_color);
		return (err("Error: allocation failed!"));
	}
	while (i < 5)
		game->textures[i++] = NULL;
	i = 0;
	while (i < 3)
		game->floor_color[i++] = 0;
	i = 0;
	while (i < 3)
		game->ceiling_color[i++] = 0;
	return (0);
}

// allocate or set some game struct members.
int	alloc_all(t_game *game, int fd)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		close(fd);
		err("Error: map allocation failed!");
		return (0);
	}
	game->map->grid = NULL;
	game->map->height = 0;
	flag_init(game);
	game->textures[4] = NULL;
	game->dir.x = 0;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0;
	game->time = 0;
	game->old_time = 0;
	game->frame_time = 0;
	return (1);
}
