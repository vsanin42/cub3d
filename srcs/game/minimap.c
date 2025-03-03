/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:33:09 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/03 19:29:55 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map_square(t_game *game, t_mimap *minimap)
{
	int	y;
	int	x;

	y = minimap->offset;
	while (y < minimap->map_side + minimap->offset)
	{
		x = minimap->offset;
		while (x < minimap->map_side + minimap->offset)
		{
			game->img.addr[y * WIN_WIDTH + x] = game->floor;
			x++;
		}
		y++;
	}
}

/* add inner layer of padding in ceiling color */

void	draw_map_padding_horizontal(t_game *game, t_mimap *minimap)
{
	int	y;
	int	y2;
	int	x;

	y = minimap->offset * 0.8;
	y2 = minimap->offset + minimap->map_side;
	while (y < minimap->offset)
	{
		x = minimap->offset * 0.8;
		while (x < minimap->offset + minimap->map_side + minimap->offset * 0.2)
		{
			game->img.addr[y * WIN_WIDTH + x] = game->ceiling;
			game->img.addr[y2 * WIN_WIDTH + x] = game->ceiling;
			x++;
		}
		y++;
		y2++;
	}
}

void	draw_map_padding_vertical(t_game *game, t_mimap *minimap)
{
	int	y;
	int	x;
	int	x2;

	y = minimap->offset * 0.8;
	while (y < minimap->offset + minimap->map_side + minimap->offset * 0.2)
	{
		x = minimap->offset * 0.8;
		x2 = minimap->offset + minimap->map_side;
		while (x < minimap->offset)
		{
			game->img.addr[y * WIN_WIDTH + x] = game->ceiling;
			game->img.addr[y * WIN_WIDTH + x2] = game->ceiling;
			x++;
			x2++;
		}
		y++;
	}
}

/* add outer layer of padding in floor color */

void	draw_map_padding_horizontal2(t_game *game, t_mimap *minimap)
{
	int	y;
	int	y2;
	int	x;

	y = minimap->offset * 0.6;
	y2 = minimap->offset + minimap->map_side + minimap->offset * 0.4;
	while (y < minimap->offset * 0.8)
	{
		x = minimap->offset * 0.6;
		while (x < minimap->offset + minimap->map_side + minimap->offset * 0.4)
		{
			game->img.addr[y * WIN_WIDTH + x] = game->floor;
			game->img.addr[y2 * WIN_WIDTH + x] = game->floor;
			x++;
		}
		y++;
		y2--;
	}
}

void	draw_map_padding_vertical2(t_game *game, t_mimap *minimap)
{
	int	y;
	int	x;
	int	x2;

	y = minimap->offset * 0.6;
	while (y < minimap->offset + minimap->map_side + minimap->offset * 0.4)
	{
		x = minimap->offset * 0.6;
		x2 = minimap->offset + minimap->map_side + minimap->offset * 0.2;
		while (x < minimap->offset * 0.8)
		{
			game->img.addr[y * WIN_WIDTH + x] = game->floor;
			game->img.addr[y * WIN_WIDTH + x2] = game->floor;
			x++;
			x2++;
		}
		y++;
	}
}

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

void	draw_minimap(t_game *game)
{
	t_mimap	minimap;
	
	minimap.offset = WIN_HEIGHT / 50;
	minimap.map_side = WIN_HEIGHT / 3.5;

	draw_map_square(game, &minimap);
	draw_map_padding_horizontal(game, &minimap);
	draw_map_padding_vertical(game, &minimap);
	draw_map_padding_horizontal2(game, &minimap);
	draw_map_padding_vertical2(game, &minimap);
	
	int	y_start = minimap.offset + minimap.map_side / 2;
	int	x_start = minimap.offset + minimap.map_side / 2;
	double step = 5.0 / (minimap.map_side / 2);
	int	y_step_count = 1;
	int	x_step_count = 1;
	double	pos_x = game->pos.x;
	double	pos_y = game->pos.y;
	int	x = x_start;
	int y = y_start;
	while (x < minimap.offset + minimap.map_side)
	{
		int g_x = pos_x + step * x_step_count;
		y = y_start;
		y_step_count = 1;
		while (y > minimap.offset)
		{
			int	g_y = pos_y - step * y_step_count;
			y_step_count++;
			if (g_y < 0
				|| g_y >= game->map->height
				|| g_x < 0
				|| g_x >= ft_strlen(game->map->grid[g_y]))
			{
				break ;
			}
			if (game->map->grid[g_y][g_x] == '0'
				|| game->map->grid[g_y][g_x] == 'N'
				|| game->map->grid[g_y][g_x] == 'S'
				|| game->map->grid[g_y][g_x] == 'W'
				|| game->map->grid[g_y][g_x] == 'E')
				game->img.addr[y * WIN_WIDTH + x] = game->ceiling;
			y--;
		}
		x_step_count++;
		x++;
	}
	draw_red_dot(game, &minimap);
}
