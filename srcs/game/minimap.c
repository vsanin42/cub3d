/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:33:09 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/02 21:11:56 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	offset = WIN_HEIGHT / 50;

int	draw_minimap(t_game *game)
{
	int ccolor;
	int	fcolor;
	int	y;
	int	x;
	int	red;
	int	map_side;

	y = offset;
	ccolor = create_trgb(0, game->ceiling_color[0],
			game->ceiling_color[1], game->ceiling_color[2]);
	fcolor = create_trgb(0, game->floor_color[0],
			game->floor_color[1], game->floor_color[2]);
	red = create_trgb(0, 255, 0, 0);
	map_side = WIN_HEIGHT / 3.5;
	// draw floor color map bg
	while (y < map_side)
	{
		x = offset;
		while (x < map_side)
		{
			game->img.addr[y * WIN_WIDTH + x] = fcolor;
			x++;
		}
		y++;
	}
	// draw ceiling color padding
	//y = offset * 0.9;
	// while (y < map_side)
	// {
	// 	y++;
	// }
	// draw red centre
	y = offset + (map_side - offset) / 2; // map center
	x = offset + (map_side - offset) / 2;
	game->img.addr[y * WIN_WIDTH + x] = red;
	return (0);
}
