/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/27 15:17:46 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

// 1. initialize the mlx, window and main image instances.
// 2. save the image address and other info in addr - needed to draw on pixels.
// 3. load textures from paths specified in textures array.
// 4. hook into key press, key release and close window events.
// 5. hook into render function as the main mlx loop function + start the loop.
int	start_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (err("Error: mlx_init() failed!:("), 0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (free(game->mlx), err("Error: mlx_new_window() failed!:("), 0);
	game->img.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = (int *)mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.size_line, &game->img.endian);
	load_textures(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 0, close_window, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (1);
}

// 1. zero out the game struct for convenience later.
// 2. check argc, if OK - allocate the key members for validation.
// 3. check map validity.
// 4. start game - load textures, setup and run mlx...
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (err("Error: Too few or many arguments!"));
	if (alloc_and_nullify(&game) == 1)
		return (1);
	if (!valid_map(argv[1], &game, 0))
		return (free_game(&game), err("Error: Map validation failed!:("));
	// print_textures(&game);
	// print_colors(&game);
	// print_map(&game);
	if (!start_game(&game))
		return (free_game(&game), 1);
	free_game(&game);
	return (0);
}
