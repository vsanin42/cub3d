/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:00:02 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/14 16:40:30 by vsanin           ###   ########.fr       */
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
