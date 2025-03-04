/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 19:33:09 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/04 17:41:25 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map_top_right(t_game *game, t_mimap *m)
{
	m->x_win = m->x_start;
	m->y_win = m->y_start;
	m->y_step_count = 1;
	m->x_step_count = 1;
	while (m->x_win < m->offset + m->map_side)
	{
		m->g_x = game->pos.x + m->step * m->x_step_count;
		m->y_win = m->y_start;
		m->y_step_count = 1;
		while (m->y_win >= m->offset)
		{
			m->g_y = game->pos.y - m->step * m->y_step_count;
			m->y_step_count++;
			if (m->g_y < 0 || m->g_y >= game->map->height || m->g_x < 0
				|| m->g_x >= ft_strlen(game->map->grid[m->g_y]))
				break ;
			if (is_floor(game, m->g_y, m->g_x))
				game->img.addr[m->y_win * WIN_WIDTH + m->x_win] = game->ceiling;
			m->y_win--;
		}
		m->x_step_count++;
		m->x_win++;
	}
}

void	draw_map_top_left(t_game *game, t_mimap *m)
{
	m->x_win = m->x_start;
	m->y_win = m->y_start;
	m->y_step_count = 1;
	m->x_step_count = 1;
	while (m->x_win >= m->offset)
	{
		m->g_x = game->pos.x - m->step * m->x_step_count;
		m->y_win = m->y_start;
		m->y_step_count = 1;
		while (m->y_win >= m->offset)
		{
			m->g_y = game->pos.y - m->step * m->y_step_count;
			m->y_step_count++;
			if (m->g_y < 0 || m->g_y >= game->map->height || m->g_x < 0
				|| m->g_x >= ft_strlen(game->map->grid[m->g_y]))
				break ;
			if (is_floor(game, m->g_y, m->g_x))
				game->img.addr[m->y_win * WIN_WIDTH + m->x_win] = game->ceiling;
			m->y_win--;
		}
		m->x_step_count++;
		m->x_win--;
	}
}

void	draw_map_bottom_right(t_game *game, t_mimap *m)
{
	m->x_win = m->x_start;
	m->y_win = m->y_start;
	m->y_step_count = 1;
	m->x_step_count = 1;
	while (m->x_win < m->offset + m->map_side)
	{
		m->g_x = game->pos.x + m->step * m->x_step_count;
		m->y_win = m->y_start;
		m->y_step_count = 1;
		while (m->y_win < m->offset + m->map_side)
		{
			m->g_y = game->pos.y + m->step * m->y_step_count;
			m->y_step_count++;
			if (m->g_y < 0 || m->g_y >= game->map->height || m->g_x < 0
				|| m->g_x >= ft_strlen(game->map->grid[m->g_y]))
				break ;
			if (is_floor(game, m->g_y, m->g_x))
				game->img.addr[m->y_win * WIN_WIDTH + m->x_win] = game->ceiling;
			m->y_win++;
		}
		m->x_step_count++;
		m->x_win++;
	}
}

void	draw_map_bottom_left(t_game *game, t_mimap *m)
{
	m->x_win = m->x_start;
	m->y_win = m->y_start;
	m->y_step_count = 1;
	m->x_step_count = 1;
	while (m->x_win >= m->offset)
	{
		m->g_x = game->pos.x - m->step * m->x_step_count;
		m->y_win = m->y_start;
		m->y_step_count = 1;
		while (m->y_win < m->offset + m->map_side)
		{
			m->g_y = game->pos.y + m->step * m->y_step_count;
			m->y_step_count++;
			if (m->g_y < 0 || m->g_y >= game->map->height || m->g_x < 0
				|| m->g_x >= ft_strlen(game->map->grid[m->g_y]))
				break ;
			if (is_floor(game, m->g_y, m->g_x))
				game->img.addr[m->y_win * WIN_WIDTH + m->x_win] = game->ceiling;
			m->y_win++;
		}
		m->x_step_count++;
		m->x_win--;
	}
}

// creates a minimap with dynamically updated surroundings.
// variables are derived from fixed values like win and height
// draw the background and padding to separate the map from the main screen
// draw walkable area in all directions in columns that begin from the center
// and extend outwards left/right/up/down
// add a red square on top of it that represents the player position
void	draw_minimap(t_game *game)
{
	t_mimap	minimap;

	minimap.offset = WIN_HEIGHT / 50;
	minimap.map_side = WIN_HEIGHT / 3.5;
	minimap.y_start = minimap.offset + minimap.map_side / 2;
	minimap.x_start = minimap.offset + minimap.map_side / 2;
	minimap.step = 5.0 / (minimap.map_side / 2);
	draw_map_square(game, &minimap);
	draw_map_padding_horizontal(game, &minimap);
	draw_map_padding_vertical(game, &minimap);
	draw_map_padding_horizontal2(game, &minimap);
	draw_map_padding_vertical2(game, &minimap);
	draw_map_top_right(game, &minimap);
	draw_map_top_left(game, &minimap);
	draw_map_bottom_right(game, &minimap);
	draw_map_bottom_left(game, &minimap);
	draw_red_dot(game, &minimap);
}
