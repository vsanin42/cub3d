/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:22:11 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/04 14:22:25 by vsanin           ###   ########.fr       */
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
