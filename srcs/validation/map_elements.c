/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/14 19:17:07 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	if_direction_p2(char *line, t_game *game, int offset)
{
	if (ft_strncmp(line + offset, "WE", 2) == 0 && line[offset + 2] == ' ')
	{
		if (game->flag_w > 0)
			return (err("Error: More than 1 texture of WE type!"), 0);
		game->textures[2] = ft_strdup(line + 3 + offset);
		game->flag_w++;
		return (1);
	}
	else if (ft_strncmp(line + offset, "EA", 2) == 0 && line[offset + 2] == ' ')
	{
		if (game->flag_e > 0)
			return (err("Error: More than 1 texture of EA type!"), 0);
		game->textures[3] = ft_strdup(line + 3 + offset);
		game->flag_e++;
		return (1);
	}
	return (0);
}

int	if_direction_p1(char *line, t_game *game, int offset)
{
	if (ft_strncmp(line + offset, "NO", 2) == 0 && line[offset + 2] == ' ')
	{
		if (game->flag_n > 0)
			return (err("Error: More than 1 texture of NO type!"), 0);
		game->textures[0] = ft_strdup(line + 3 + offset);
		game->flag_n++;
		return (1);
	}
	else if (ft_strncmp(line + offset, "SO", 2) == 0 && line[offset + 2] == ' ')
	{
		if (game->flag_s > 0)
			return (err("Error: More than 1 texture of SO type!"), 0);
		game->textures[1] = ft_strdup(line + 3 + offset);
		game->flag_s++;
		return (1);
	}
	return (0);
}

int	if_surface(char *line, t_game *game, int offset)
{
	if (ft_strncmp(line + offset, "F ", 2) == 0)
	{
		if (!save_color_floor(line + offset, game, 0, 0))
			return (err("Error: Problem with floor color!"), 0);
		game->flag_f++;
		return (1);
	}
	else if (ft_strncmp(line + offset, "C ", 2) == 0)
	{
		if (!save_color(line + offset, game, 0, 0))
			return (err("Error: Problem with ceiling color!"), 0);
		game->flag_c++;
		return (1);
	}
	return (0);
}

int	if_line_1(char *line, t_game *game, int *map_flag)
{
	// do this first to avoid extra malloc calls if textures/floor/ceiling wasn't set
	if (game->flag_n != 1 || game->flag_w != 1 || game->flag_e != 1
		|| game->flag_s != 1 || game->flag_f != 1 || game->flag_c != 1)
		return (err("Error: Map found before all NSWEFC elements!"), 0);
	*map_flag = 1;
	if (!add_map_line(game->map, line))
		return (err("Error: New grid line allocation failed!"), 0);
	return (1);
}

int	if_map(char *line, t_game *game, int *map_flag, int offset)
{
	if (*map_flag == -1 && (line[offset] > 32 && line[offset] < 127))
		return (err("Error: Extra content after map!"), 0);
	else if (line[offset] == '1')
	{
		if (!if_line_1(line, game, map_flag))
			return (0);
	}
	else if (*map_flag == 1 && line[offset] == '\n')
		*map_flag = -1;
	else if (line[offset] == '\n')
		;
	else if (line[offset] == '0')
		return (err("Error: Open area detected (at line start)!"), 0);
	else
		return (0);
	return (1);
}
