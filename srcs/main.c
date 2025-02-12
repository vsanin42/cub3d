/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/12 14:30:24 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err(char *text_err)
{
	printf("%s\n", text_err);
	return (-1);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	if (map->grid)
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

void	set_array_as_null(char **textures, int *floor_color, int *ceiling_color)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		textures[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		floor_color[i] = 0;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		ceiling_color[i] = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc == 2)
	{
		game.textures = malloc(5 * sizeof(char *));
		game.floor_color = malloc(3 * sizeof(int));
		game.ceiling_color = malloc(3 * sizeof(int));
		if (!game.textures || !game.floor_color || !game.ceiling_color)
		{
			free_game(&game);
			return (err("Error: Memory allocation failed!"));
		}
		set_array_as_null(game.textures, game.floor_color, game.ceiling_color);
		if (!valid_map(argv[1], &game, 0))
		{
			free_game(&game);
			return (err("Error: Not a valid map!:("));
		}
		start_game(&game);
		free_game(&game);
	}
	else
		return (err("Error: Too few or many arguments!"));
	return (0);
}
