/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/13 15:00:53 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err(char *text_err)
{
	printf("%s\n", text_err);
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

// not used if we keep alloc_and_nullify
void	set_array_as_null(char **textures, int *floor_color, int *ceiling_color)
{
	int	i;

	i = 0;
	while (i < 5)
		textures[i++] = NULL;
	i = 0;
	while (i < 3)
		floor_color[i++] = 0;
	i = 0;
	while (i < 3)
		ceiling_color[i++] = 0;
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

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (err("Error: Too few or many arguments!"));
	if (alloc_and_nullify(&game) == 1)
		return (1);
	// set_array_as_null(game.textures, game.floor_color, game.ceiling_color);
	if (!valid_map(argv[1], &game, 0))
		return (free_game(&game), err("Error: Not a valid map!:("));
	start_game(&game);
	free_game(&game);
	return (0);
}
