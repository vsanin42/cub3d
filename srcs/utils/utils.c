/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:00:02 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/14 22:32:35 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	err(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map) // map is always alloced in alloc_all but keep it
		return ;
	if (!map->grid) // grid may not be alloced if textures/floor/ceiling is missing
		return (free(map)); // in that case only free the map and exit
	while (i < map->height) // otherwise free each grid line, grid itself and finally map
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	free(map);
}

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
