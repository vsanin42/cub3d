/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/16 21:42:06 by vsanin           ###   ########.fr       */
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
	// destroy images
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

int	start_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (err("Error: mlx_init() failed!:("), 0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (free(game->mlx), err("Error: mlx_new_window() failed!:("), 0);
	// todo img and addr (?)
	// todo load textures
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 1L << 0, close_window, game);
	// todo render everything initially (or not?)
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (1);
}
