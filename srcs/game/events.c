/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:31:11 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/27 15:35:30 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// setting like this could be bad - edit: idk what i meant by this
// 
int	key_press_wasd(t_game *game, int keycode)
{
	if (keycode == XK_w)
	{
		game->keymap.w = true;
		// update_pos(game, game->dir.x, game->dir.y);
	}
	if (keycode == XK_s)
	{
		game->keymap.s = true;
		// update_pos(game, -game->dir.x, -game->dir.y);
	}
	if (keycode == XK_a)
	{
		game->keymap.a = true;
		// update_pos(game, -game->plane.x, -game->plane.y);
	}
	if (keycode == XK_d)
	{
		game->keymap.d = true;
		// update_pos(game, game->plane.x, game->plane.y);
	}
	return (0);
}

// derived these values from printing keycodes:
// W	119
// A	97
// S	115
// D	100
// L	65361
// R	65363
// ESC	65307
// might not work on other systems, so i'm using Xlib keysyms.
// they all correspond to the above.
// this only changes the bools in the keymap, they get back to false on release.
int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	if (keycode == XK_w || keycode == XK_a
		|| keycode == XK_s || keycode == XK_d)
		key_press_wasd(game, keycode);
	if (keycode == XK_Left)
	{
		game->keymap.l = true;
	}
	if (keycode == XK_Right)
	{
		game->keymap.r = true;
	}
	return (0);
}

// reset the keymap bool on key release to indicate it's no longer pressed.
int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keymap.w = false;
	if (keycode == XK_s)
		game->keymap.s = false;
	if (keycode == XK_a)
		game->keymap.a = false;
	if (keycode == XK_d)
		game->keymap.d = false;
	if (keycode == XK_l)
		game->keymap.l = false;
	if (keycode == XK_r)
		game->keymap.r = false;
	return (0);
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
