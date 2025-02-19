/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:54:59 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/19 19:38:11 by vsanin           ###   ########.fr       */
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

// gets the correct texture depending on the side that was hit
t_image	*get_nswe_tex(t_game *game, t_side nswe)
{
	if (nswe == NORTH)
		return (&game->north);
	if (nswe == SOUTH)
		return (&game->south);
	if (nswe == WEST)
		return (&game->west);
	if (nswe == EAST)
		return (&game->east);
	return (NULL);
}

// now we need to draw the line.
// 1. we get the texture to draw from.
// 2. we set y as draw start and iterate until draw end, drawing the full line.
// 3. step tells us how many texture pixels correspond to one screen pixel - scaling variable.
// 4. tex pos is the position on the texture to start drawing from.
// calculated by substracting the perfectly sized position from the real intended position and multiplyin by step to get the texture position.
// 5. loop from top to bottom.
// 5.1. tex_y is the exact y coordinate of the texture. together with tex_x it allows us to reach the desired pixel.
// & (TEX_HEIGHT - 1) is a bitwise operation that acts like a mask to prevent undefined behaviour, makes it wrap around.
// 5.2. each time we draw, we move over in texture position by the defined step.
// 5.3. color will hold the value of a pixel at [tex_y][tex_x] in the texture. it is then assigned to the [y][x] position on the real screen image.
void	draw_line(t_ray *r, t_game *game, int x)
{
	int		y;
	t_image	*tex;
	int		color;

	tex = get_nswe_tex(game, r->nswe);
	y = r->draw_start;
	r->draw_step = (double)TEX_HEIGHT / r->line_height;
	r->tex_pos = (y - WIN_HEIGHT / 2 + r->line_height / 2) * r->draw_step;
	while (y < r->draw_end)
	{
		r->tex_y = (int)r->tex_pos & (TEX_HEIGHT - 1); // only works if TEX_HEIGHT is a power of 2. otherwise use % TEX_HEIGHT
		r->tex_pos += r->draw_step;
		color = tex->addr[r->tex_y * TEX_WIDTH + r->tex_x];
		game->img.addr[y * WIN_WIDTH + x] = color;
		y++;
	}
}

// this is in mlx_loop_hook
// 1. t_ray r holds all variables we're working with.
// 2. for every x (column) of the screen width, going from left to right, perform the raycasting process.
// 3. set the variables of r struct.
// 4. run the dda algorithm to cast a ray in a specific direction until it hits a wall.
// by the end of dda() function, we have all the info we need to draw a single vertical line of a needed size.
// it's all stored in the r struct.
// 5. move onto the next x column of the screen, cast a ray, find the line height, repeat until WIN_WIDTH.
// 6. set_frame_time() tracks time between two frames created. - WIP
// 7. put the created image to the window.
int	render(t_game *game)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_memset(&r, 0, sizeof(t_ray)); // just in case
		set_ray_variables(&r, game, x);
		dda(&r, game);
		draw_line(&r, game, x);
		x++;
	}
	set_frame_time(game);
	// any buffer clearing of the last image? idk
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}
