/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:47 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/02 18:56:32 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// event handler for mouse entering the window.
// only sets the respective bool to true. optional: hide mouse while in window.
// mlx_mouse_hide(game->mlx, game->win);
int	mouse_enter(t_game *game)
{
	game->mouse_in_window = true;
	return (0);
}

// event handler for mouse leaving the window.
// only sets the respective bool to false. optional: show mouse while in window.
// mlx_mouse_show(game->mlx, game->win);
int	mouse_leave(t_game *game)
{
	game->mouse_in_window = false;
	return (0);
}

// update the mouse coordinates with the new ones.
int	mouse_move(int x, int y, t_game *game)
{
	game->mouse.x = x;
	game->mouse.y = y;
	return (0);
}

// rotate the POV - same logic as with arrow keys but with the mouse inputs.
// 1. check if the previous saved position and the current one are different.
// 1.1. check if mouse is outside of window. if either is true - exit.
// 2. calcualte the difference between old and new x coords, don't care about y.
// 3. do NOT scale with rot_speed like with arrow keys!
// it's different, so to avoid FPS-dependent rotations,
// just minimize the diff based on preferred sensitivity (in the header file).
// 4. rotate with rotation matrix.
int	update_mouse_cam(t_game *game)
{
	int		cur_x;
	int		cur_y;
	int		diff;
	double	angle;

	mlx_mouse_get_pos(game->mlx, game->win, &cur_x, &cur_y);
	if (game->mouse.x == cur_x || game->mouse_in_window == false)
		return (1);
	diff = cur_x - game->mouse.x;
	angle = diff * MOUSE_SENSITIVITY;
	rotation_matrix(game, angle);
	return (0);
}

// perform rotation matrix multiplication to update the camera.
// angle is rot_speed, sign set either from arrows or mouse movement.
void	rotation_matrix(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->dir.x;
	old_plane_x = game->plane.x;

	game->dir.x = old_dir_x * cos(angle) - game->dir.y * sin(angle);
	game->dir.y = old_dir_x * sin(angle) + game->dir.y * cos(angle);
	game->plane.x = old_plane_x * cos(angle) - game->plane.y * sin(angle);
	game->plane.y = old_plane_x * sin(angle) + game->plane.y * cos(angle);
}
