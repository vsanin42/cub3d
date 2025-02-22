/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/19 19:23:16 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// currently not in use, freeing is done in main
void	err_exit(char *err_msg, t_game *game)
{
	free_game(game);
	err(err_msg);
	exit(1);
}

int	close_window(t_game *game)
{
	mlx_destroy_image(game->mlx, game->north.ptr);
	mlx_destroy_image(game->mlx, game->south.ptr);
	mlx_destroy_image(game->mlx, game->west.ptr);
	mlx_destroy_image(game->mlx, game->east.ptr);
	mlx_destroy_image(game->mlx, game->img.ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_game(game);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_window(game);
	// todo
	return (0);
}

void	load_textures(t_game *game)
{
	game->north.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[NORTH],
			&game->north.w, &game->north.h);
	game->south.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[SOUTH],
			&game->south.w, &game->south.h);
	game->west.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[WEST],
			&game->west.w, &game->west.h);
	game->east.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[EAST],
			&game->east.w, &game->east.h);
	game->north.addr = (int *)mlx_get_data_addr(game->north.ptr,
			&game->north.bpp, &game->north.size_line, &game->north.endian);
	game->south.addr = (int *)mlx_get_data_addr(game->south.ptr,
			&game->south.bpp, &game->south.size_line, &game->south.endian);
	game->west.addr = (int *)mlx_get_data_addr(game->west.ptr,
			&game->west.bpp, &game->west.size_line, &game->west.endian);
	game->east.addr = (int *)mlx_get_data_addr(game->east.ptr,
			&game->east.bpp, &game->east.size_line, &game->east.endian);
}

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
	mlx_hook(game->win, 17, 1L << 0, close_window, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (1);
}
