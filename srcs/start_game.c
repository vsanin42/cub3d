/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/13 23:35:59 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	err_exit(char *err_msg, t_game *game)
{
	free_game(game);
	err(err_msg);
	exit(1);
}

int	close_window(t_win_params *wind)
{
	mlx_destroy_window(wind->mlx, wind->win);
	free_game(wind->game);
	exit(0);
}

int	key_press(int keycode, t_win_params *wind)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(wind->mlx, wind->win);
		free_game(wind->game);
		exit(0);
	}
	return (0);
}

void	start_game(t_game *game)
{
	t_win_params	wind;

	wind.mlx = mlx_init();
	if (!wind.mlx)
		err_exit("Error: Something is wrong with window!", game);
	wind.win = mlx_new_window(wind.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!wind.win)
		err_exit("Error: Something is wrong with window!", game);
	wind.game = game;
	mlx_key_hook(wind.win, key_press, &wind);
	mlx_hook(wind.win, 17, 0, close_window, &wind);
	mlx_loop(wind.mlx);
}
