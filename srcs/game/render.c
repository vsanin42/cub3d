/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:47:13 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/27 17:32:05 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// draw rgb color line to create the floor
// might need to pass 255 instead of 0 as t param in trgb
// 1. check if draw_end of the texture line (start for the floor)
// is at the window border. if yes, don't draw anything and return.
// 2. create the trgb value from the floor colors from the map file.
// 3. set the beginning of the floor drawing as the last point of texture drawn.
// 4. fill the main image pixels with the floor color until the window border.
// otherwise same logic as in the draw line function.
void	draw_floor(t_ray *r, t_game *game, int x)
{
	int	start;
	int	color;

	if (r->draw_end == WIN_HEIGHT - 1)
		return ;
	color = create_trgb(0, game->floor_color[0],
			game->floor_color[1], game->floor_color[2]);
	start = r->draw_end;
	while (start < WIN_HEIGHT)
	{
		game->img.addr[start * WIN_WIDTH + x] = color;
		start++;
	}
}

// draw rgb color line to create the ceiling
// might need to pass 255 instead of 0 as t param in trgb
// 1. check if draw_start of the texture line (start for the ceiling) is at the window border
// if yes, don't draw anything and return.
// 2. create the trgb value from the ceiling colors from the map file.
// 3. set the end of the ceiling drawing as the first point of texture drawn. start is simply 0.
// 4. fill the main image pixels with the ceiling color until the the first point of texture.
// otherwise same logic as in the draw line function.
void	draw_ceiling(t_ray *r, t_game *game, int x)
{
	int	start;
	int	color;

	if (r->draw_start == 0)
		return ;
	color = create_trgb(0, game->ceiling_color[0],
			game->ceiling_color[1], game->ceiling_color[2]);
	start = 0;
	while (start < r->draw_start)
	{
		game->img.addr[start * WIN_WIDTH + x] = color;
		start++;
	}
}

// now we need to draw the line.
// 1. we get the texture to draw from.
// 2. we set y as draw start and iterate until draw end, drawing the full line.
// 3. step tells us how many texture pixels correspond to one screen pixel.
// 4. tex pos is the position on the texture to start drawing from.
// calculated by substracting the perfectly sized position
// from the intended position and multiplying by step to get the tex position.
// 5. loop from top to bottom.
// 5.1. tex_y is the exact y coordinate of the texture.
// together with tex_x it allows us to reach the desired pixel.
// & (TEX_HEIGHT - 1) is a bitwise operation that acts like a mask
// to prevent undefined behaviour, makes it wrap around.
// 5.2. each time we draw, we move over in texture position by the defined step.
// 5.3. color will hold the value of a pixel at [tex_y][tex_x] in the texture.
// it is then assigned to the [y][x] position on the real screen image.
void	draw_line(t_ray *r, t_game *game, int x)
{
	int		y;
	t_image	*tex;
	int		color;

	tex = get_nswe_tex(game, r->nswe);
	y = r->draw_start;
	r->draw_step = (double)TEX_HEIGHT / r->line_height;
	r->tex_pos = (y - WIN_HEIGHT / 2 + r->line_height / 2) * r->draw_step;
	draw_ceiling(r, game, x);
	while (y < r->draw_end)
	{
		r->tex_y = (int)r->tex_pos & (TEX_HEIGHT - 1); // only works if TEX_HEIGHT is a power of 2. otherwise use % TEX_HEIGHT
		r->tex_pos += r->draw_step;
		color = tex->addr[r->tex_y * TEX_WIDTH + r->tex_x];
		game->img.addr[y * WIN_WIDTH + x] = color;
		y++;
	}
	draw_floor(r, game, x);
}

// perform movements: position or camera.
// if WASD are pressed:
// update the player's position depending on the key that's currently pressed.
// if LR arrows are pressed:
// rotate the camera.
void	move(t_game *game)
{
	if (game->keymap.w == true)
		update_pos(game, game->dir.x, game->dir.y);
	if (game->keymap.s == true)
		update_pos(game, -game->dir.x, -game->dir.y);
	if (game->keymap.a == true)
		update_pos(game, -game->plane.x, -game->plane.y);
	if (game->keymap.d == true)
		update_pos(game, game->plane.x, game->plane.y);
	if (game->keymap.l == true || game->keymap.r == true)
		update_cam(game);
}

// main rendering function.
// 1. t_ray r holds all variables we're working with.
// 2. for every x (column) of the screen width, going from left to right,
// perform the raycasting process.
// 2.1 to make sure the ray is clear for each iteration, zero it out w/ memset.
// 3. set the variables of r struct.
// 4. run the dda algorithm to cast a ray in a specific direction
// until it hits a wall. by the end of dda() function,
// we have all the info we need to draw a single vertical line of a needed size.
// it's all stored in the r struct.
// 5. move onto the next x column of the screen, cast a ray,
// find the line height, repeat until WIN_WIDTH.
// 6. set_frame_time() tracks time between two frames created.
// 7. update player position. safer to do it here, only sacrificing one frame.
// with in infinite mlx loop, it's incredibly unlikely, but not impossible,
// that you can move before the first frames are drawn, meaning move_speed == 0,
// meaning the position update will be at 0, 0, which can be empty -> segfault.
// 8. put the created image to the window.
int	render(t_game *game)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_memset(&r, 0, sizeof(t_ray));
		set_ray_variables(&r, game, x);
		dda(&r, game);
		draw_line(&r, game, x);
		x++;
	}
	set_frame_time(game);
	move(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}
