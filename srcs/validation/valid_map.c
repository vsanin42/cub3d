/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/15 01:00:48 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	alloc_all(t_game *game, int fd)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
	{
		close(fd);
		err("Error: map allocation failed!");
		return (0);
	}
	game->map->grid = NULL;
	game->map->height = 0;
	flag_init(game);
	game->textures[4] = NULL;
	game->dir.x = 0;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0;
	game->time = 0;
	game->old_time = 0;
	return (1);
}

int	save_and_check(int *map_flag, t_game *game, char *line)
{
	int	offset;
	int	res1;
	int	res2;
	int	res3;
	int	res4;

	offset = skip_whitespace(line);
	res1 = if_direction_p2(line, game, offset);
	res2 = if_direction_p1(line, game, offset);
	res3 = if_surface(line, game, offset);
	res4 = if_map(line, game, map_flag, offset);
	if (!res1 && !res2 && !res3 && !res4)
	{
		// cleans whatever remains in the buffer if stopped reading in the middle of file
		get_next_line(-1);
		free(line);
		return (0);
	}
	return (1);
}

int	check_fd(int fd)
{
	if (fd == -1)
	{
		if (errno == ENOENT)
			err("Error: File doesn't exist!");
		else if (errno == EACCES)
			err("Error: Permission denied!");
		else if (errno == EISDIR)
			err("Error: Trying to open a directory!");
		else
			err("Error: Opening file failed!");
		return (-1);
	}
	return (0);
}

// this check is unnecessary because if if it's too small,
// then other checks will catch it. but let's keep  it
int	check_height(int height)
{
	if (height < 3)
		return (err("Error: The map is too small!"), 0);
	return (1);
}

int	valid_map(char *argv, t_game *game, int fd)
{
	char	*line;
	int		map_flag;

	fd = open(argv, O_RDONLY); 
	if (check_fd(fd) == -1 || !check_format(argv, fd) || !alloc_all(game, fd)) // + close(fd) inside both if error
		return (0);
	line = get_next_line(fd);
	map_flag = 0;
	while (line != NULL)
	{
		if (!save_and_check(&map_flag, game, line))
			return (close(fd), 0); // + close(fd)
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->flag_n != 1 || game->flag_w != 1 || game->flag_e != 1
		|| game->flag_s != 1 || game->flag_f != 1 || game->flag_c != 1
		|| map_flag == 0) // is map_flag == 0 enough to check? 
		return (err("Error: Missing/extra textures, colors and/or map!"), 0);
	if (!check_height(game->map->height) || !check_player(game->map->grid, game)
		|| !check_walls(game->map->grid, game->map->height)
		|| !edit_paths(game->textures))
		return (0);
	return (1);
}
