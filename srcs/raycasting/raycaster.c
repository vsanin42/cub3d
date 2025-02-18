/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:54:59 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/18 17:13:00 by vsanin           ###   ########.fr       */
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
// if a wall was hit (grid[y][x] == '1'), set hit and nswe in helper and exit the loop.
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
		if (game->map->grid[r->map_y][r->map_x] == '1') // possibly swap y and x if doesn't work?
			set_hit_and_nswe(r);
	}
	set_final_vars(r, game);
}

void	draw_line(t_ray *ray, t_game *game)
{
	// TODO, still researching
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
		draw_line(&r, game);
		x++;
	}
	set_frame_time(game);

	// draw everything (i guess push the image to the window?)
	// any buffer clearing of the last image? idk
	return (0);
}
