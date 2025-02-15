/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:54:59 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/15 19:24:05 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// calculate the step (used to specify which way the ray moves in the dda algorithm)
// and side dist (distance from ray start to the first x/y side)
// negative direction = negative step, etc...
void	set_step_and_side(t_ray *r, t_game *game)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->pos.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1 - game->pos.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->pos.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1 - game->pos.y) * r->delta_dist_y;
	}
}

void	set_ray_variables(t_ray *r, t_game *game, int x)
{
	// calculate the current ray direction coordinates
	r->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	r->ray_dir_x = game->dir.x + game->plane.x * r->camera_x;
	r->ray_dir_y = game->dir.y + game->plane.y * r->camera_x;

	// track the square of the map we're in (ignores decimal part and keeps int)
	r->map_x = (int)game->pos.x;
	r->map_y = (int)game->pos.y;

	// do the following to avoid dividing by 0
	// dir coordinate being 0 = the direction is either perfectly vertical or horizontal.
	// that means the delta dist should indicate that we'll never hit a wall in that direction
	// example: going perfectly east, a ray will never hit the north/south wall.
	// if 0, make it a very large value (one we won't ever find in any map)
	// else find absolute value of a double in brackets (fabs instead of abs)
	// (idk the calculations that led to this lol so it's just this formula)
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);

	// same for dir y
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	
	// this will help keep track if we've hit a wall
	r->hit = 0;

	set_step_and_side(r, game);
}

// digital differential analysis algorithm.
// logic:
// depending on which distance is shorter (to the next x or y side)
// advance the ray towards that side by delta dist.
// after that, depending on the step (+-1) taken in that direction, update:
// the map square it just hit + the type of side that was hit (NS or WE).
// after this is done, the ray stops at a border of square.
// thanks to map x and y we know the coordinates of this square.
// using this x and y check the map grid for what value is in that square.
// if a wall was hit (grid[y][x] == '1'), set hit to 1 and exit the loop.
void	dda(t_ray *r, t_game *game)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;	
		}
		if (game->map->grid[r->map_y][r->map_x] == '1') // possibly swap y and x if doesn't work?
			r->hit = 1;
	}
}

// this is probably going to replace render (function in mlx_loop_hook) (also rename to smth nice)
// 1. t_ray r holds all variables we're working with.
// 2. for every x (column) of the screen width, perform the raycast.
// 3. set the variables of r struct.
// 4. run the dda algorithm until a ray hits a wall.
int	raycaster_main(t_game *game)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < WIN_WIDTH)
	{
		set_ray_variables(&r, game, x);
		dda(&r, game);
		x++;
	}
}
