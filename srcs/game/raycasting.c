/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:51:59 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/04 17:39:40 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// digital differential analysis algorithm.
// logic:
// depending on which distance is shorter (to the next x or y side)
// advance the ray towards that side by delta dist.
// after that, depending on the step (+-1) taken in that direction, update:
// the map square it just hit + the type of side that was hit (NS or WE).
// after this is done, the ray stops at a border of square.
// thanks to map x and y we know the coordinates of this square.
// using this x and y check the map grid for what value is in that square.
// if a wall was hit (grid[y][x] == '1'), set hit and nswe in helper function
// and exit the loop.
// the last variables we need to set are done in the helper function.
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
		if (game->map->grid[r->map_y][r->map_x] == '1')
			set_hit_and_nswe(r);
	}
	set_final_vars(r, game);
}

// calculate the step (used to specify which way the ray should move in dda)
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

// 1. calculate the current ray direction coordinates
// 2. track the square of the map we're in (ignores decimal part and keeps int)
// 3. do the following to avoid dividing by 0:
// dir coordinate 0 = the direction is either perfectly vertical or horizontal.
// that means the delta dist should indicate
// that we'll never hit a wall in that direction.
// example: going perfectly east, a ray will never hit the north/south wall.
// if 0, make it a very large value (one we won't ever find in any map)
// else find absolute value of a double in brackets.
// this achieves proper comparison between side dist x and y later.
// 4. hit indicates if a wall was hit. also some more vars to be defined.
void	set_ray_variables(t_ray *r, t_game *game, int x)
{
	r->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	r->ray_dir_x = game->dir.x + game->plane.x * r->camera_x;
	r->ray_dir_y = game->dir.y + game->plane.y * r->camera_x;
	r->map_x = (int)game->pos.x;
	r->map_y = (int)game->pos.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	r->hit = 0;
	set_step_and_side(r, game);
}

// 1. depending on which side was hit, calculate the distance
// from the camera plane to the wall. it's perpendicular to
// the camera plane/our screen and remains fixed to avoid fisheye effect.
// 2. calculate the height of the line to be drawn - depends on the perp dist.
// 3. set the start/end points of the line we want to draw.
// start point - the higher one. end point - the lower one.
// 3.1. WIN_HEIGHT / 2 centers the point.
// 3.2. for start, we subtract half of the line height,
// so the start point will be between the center and the top of the screen.
// if the projected point is above the top of the screen, hard set it to 0.
// 3.3. for end, we add half of the line height,
// so the end point will be between the center and the bottom of the screen.
// if the projected point is above the bottom of the screen, hard set it to
// WIN_HEIGHT - 1 (last drawable pixel).
// 4. find the x coordinate (column) of the square that was just hit
// - needed to know which texture column to draw.
// floor() returns the closest integer - rounds down. when subtracted,
// wall_x becomes a value between 0 and 1.
// this only tells us how far left or right (on a scale from 0 to 1)
// the required texture line would be, not which line it is.
// 5. this decimal value needs to be scaled to the texture width to find
// the actual pixel stripe value.
// note: value of WIN_HEIGHT can be multiplied by something
// to make the walls taller, but no need.
void	set_final_vars(t_ray *r, t_game *game)
{
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	r->draw_start = WIN_HEIGHT / 2 - r->line_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = WIN_HEIGHT / 2 + r->line_height / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
	if (r->side == 0)
		r->wall_x = game->pos.y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = game->pos.x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);
}

// i really hope this works. xd
// 1. setting hit to 1 lets us exit the loop.
// 2. then we figure out which exact side was hit.
// this is done with side variable:
// 0 or 1 already limits the choices to N/S and W/E
// then the step variable tells which way we were moving.
// example: side == 0 - vertical (x) side was hit - EAST OR WEST?
// step == 1 - we were going right (EAST) - texture facing WEST.
// step == 0 - ... - EAST. same for N/S.
void	set_hit_and_nswe(t_ray *r)
{
	r->hit = 1;
	if (r->side == 0)
	{
		if (r->step_x == 1)
			r->nswe = WEST;
		else if (r->step_x == -1)
			r->nswe = EAST;
	}
	else if (r->side == 1)
	{
		if (r->step_y == 1)
			r->nswe = NORTH;
		else if (r->step_y == -1)
			r->nswe = SOUTH;
	}
}
