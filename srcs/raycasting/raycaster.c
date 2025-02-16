/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:54:59 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/16 21:43:19 by vsanin           ###   ########.fr       */
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
	// else find absolute value of a double in brackets (fabs instead of abs) !!! (possibly may need abs)
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

// this makes sense for untextured raycaster, will see if it applies to textured.
// start point - the higher one. end point - the lower one.
// 1. WIN_HEIGHT / 2 centers the point.
// 2. for start, we subtract half of the line height,
// so the start point will be between the center and the top of the screen.
// if the projected point is above the top of the screen, hard set it to 0.
// 3. for end, we add half of the line height,
// so the end point will be between the center and the bottom of the screen.
// if the projected point is above the bottom of the screen, hard set it to WIN_HEIGHT - 1 (last drawable pixel).
void	set_draw_start_end(t_ray *r)
{
	r->draw_start = WIN_HEIGHT / 2 - r->line_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = WIN_HEIGHT / 2 + r->line_height / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
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
// depending on which side was hit, calculate the distance from the camera plane to the wall.
// it's perpendicular to the camera plane/our screen and remains fixed to avoid fisheye effect.
// calculate the height of the line to be drawn - depends on the perp distance above.
// the last thing we need is the start/end points of the line we want to draw, done in the helper.
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
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	// value of WIN_HEIGHT below can be changed (multiplied by a number) to make walls higher/lower
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	set_draw_start_end(r);
}

// this is in mlx_loop_hook
// 1. t_ray r holds all variables we're working with.
// 2. for every x (column) of the screen width, going from left to right, perform the raycasting process.
// 3. set the variables of r struct.
// 4. run the dda algorithm to cast a ray in a specific direction until it hits a wall.
// by the end of dda() function, we have all the info we need to draw a single vertical line of a needed size.
// it's all stored in the r struct.
// . move onto the next x column of the screen, cast a ray, find the line height, repeat until WIN_WIDTH.
int	render(t_game *game)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < WIN_WIDTH)
	{
		set_ray_variables(&r, game, x);
		dda(&r, game);
		// draw the vertical line - big TODO
		x++;
	}
	game->old_time = game->time; // set time and old_time to define fps once the whole image is drawn
	game->time = get_current_time(); // get_current_time returns seconds (in long), might need more precision
	game->frame_time = (game->time - game->old_time);
	printf("FPS: %f\n", 1 / game->frame_time); // optional?

	// draw everything (i guess push the image to the window?)
	// any buffer clearing of the last image? idk
}
