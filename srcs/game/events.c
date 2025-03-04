/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:31:11 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/04 17:35:26 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// cleanup function: destroy loaded images, window, mlx, free everything.
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

// using Xlib values for keysyms.
// they all correspond to the above.
// this only changes the bools in the keymap, they get back to false on release.
int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	if (keycode == XK_w)
		game->keymap.w = true;
	if (keycode == XK_s)
		game->keymap.s = true;
	if (keycode == XK_a)
		game->keymap.a = true;
	if (keycode == XK_d)
		game->keymap.d = true;
	if (keycode == XK_Left)
		game->keymap.l = true;
	if (keycode == XK_Right)
		game->keymap.r = true;
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
	if (keycode == XK_Left)
		game->keymap.l = false;
	if (keycode == XK_Right)
		game->keymap.r = false;
	return (0);
}

// update the position after checking for collisions.
// check if the projected position after moving ends up inside a wall.
// checking the point itself is not safe.
// imagine two walls touching by their corners.
// if the moving step allows for it, it's possible to step through them,
// even though the other side is not even visible.
// so instead of checking the point itself,
// check the 4 grid directions relative to that point, in NSWE order below.
// if any of the directions is a wall, don't perform the move.
// if all OK, update pos - x and y increments are already passed as params.
// how close to a wall you can possibly get is determined by step.
// it can be modified, but >0.5 would make passing between two walls impossible.
int	update_pos(t_game *game, double x, double y)
{
	t_pos	proj;
	double	step;

	step = 0.15;
	proj.x = game->pos.x + x * game->move_speed;
	proj.y = game->pos.y + y * game->move_speed;
	if (game->map->grid[(int)(proj.y - step)][(int)proj.x] == '1')
		return (0);
	if (game->map->grid[(int)(proj.y + step)][(int)proj.x] == '1')
		return (0);
	if (game->map->grid[(int)proj.y][(int)(proj.x - step)] == '1')
		return (0);
	if (game->map->grid[(int)proj.y][(int)(proj.x + step)] == '1')
		return (0);
	game->pos.x += x * game->move_speed;
	game->pos.y += y * game->move_speed;
	return (1);
}

// rotate the POV left or right.
// use the rot_speed derived from FPS as angle, adjust based on L/R arrow.
// perform rotation matrix multiplication to update the camera.
int	update_cam(t_game *game)
{
	double	angle;

	angle = 0;
	if (game->keymap.l == true)
		angle = -game->rot_speed;
	else if (game->keymap.r == true)
		angle = game->rot_speed;
	rotation_matrix(game, angle);
	return (0);
}
