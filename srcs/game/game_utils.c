/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:43:02 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/04 17:41:06 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// set time and old_time to determine fps once the whole image is drawn
// get_current_time() returns milliseconds (in long), might need more precision.
// 5 and 3 are const values, in squares/s and radians/s respectively.
// to print FPS: printf("FPS: %.0f\n", 1 / game->frame_time);
void	set_frame_time(t_game *game)
{
	game->old_time = game->time;
	game->time = get_current_time();
	game->frame_time = (game->time - game->old_time) / (double)1000;
	game->move_speed = game->frame_time * 5;
	game->rot_speed = game->frame_time * 3;
}

// gets the correct texture depending on the side that was hit by the ray.
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

// 1. load the textures from xpm files specified by the paths in game->textures.
// 2. to access their individual pixels, store their addresses in addr.
// bits per pixel, line size an endian are not used, but need to be stored.
void	load_textures(t_game *game)
{
	game->north.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[NORTH],
			&game->north.w, &game->north.h);
	game->south.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[SOUTH],
			&game->south.w, &game->south.h);
	game->west.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[WEST],
			&game->west.w, &game->west.h);
	game->east.ptr = mlx_xpm_file_to_image(game->mlx, game->textures[EAST],
			&game->east.w, &game->east.h);
	game->north.addr = (int *)mlx_get_data_addr(game->north.ptr,
			&game->north.bpp, &game->north.size_line, &game->north.endian);
	game->south.addr = (int *)mlx_get_data_addr(game->south.ptr,
			&game->south.bpp, &game->south.size_line, &game->south.endian);
	game->west.addr = (int *)mlx_get_data_addr(game->west.ptr,
			&game->west.bpp, &game->west.size_line, &game->west.endian);
	game->east.addr = (int *)mlx_get_data_addr(game->east.ptr,
			&game->east.bpp, &game->east.size_line, &game->east.endian);
	game->floor = create_trgb(0, game->floor_color[0],
			game->floor_color[1], game->floor_color[2]);
	game->ceiling = create_trgb(0, game->ceiling_color[0],
			game->ceiling_color[1], game->ceiling_color[2]);
}

// used in minimap to check the value of a grid square
int	is_floor(t_game *game, int g_y, int g_x)
{
	if (game->map->grid[g_y][g_x] == '0'
		|| game->map->grid[g_y][g_x] == 'N'
		|| game->map->grid[g_y][g_x] == 'S'
		|| game->map->grid[g_y][g_x] == 'W'
		|| game->map->grid[g_y][g_x] == 'E')
		return (1);
	return (0);
}

// draws red dot for the center of the minimap
void	draw_red_dot(t_game *game, t_mimap *minimap)
{
	int	y;
	int	x;
	int	half_side;
	int	dot_half_side;

	half_side = minimap->map_side / 2;
	dot_half_side = minimap->map_side * 0.025;
	y = minimap->offset + half_side - dot_half_side;
	while (y < minimap->offset + half_side + dot_half_side)
	{
		x = minimap->offset + half_side - dot_half_side;
		while (x < minimap->offset + half_side + dot_half_side)
		{
			game->img.addr[y * WIN_WIDTH + x] = RED;
			x++;
		}
		y++;
	}
}
