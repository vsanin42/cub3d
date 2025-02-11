/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/02/09 22:00:46 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	alloc_all(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (0);
	game->map->grid = NULL;
	game->map->height = 0;
	flag_init(game);
	game->textures[4] = NULL;
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
		free(line);
		return (0);
	}
	return (1);
}

int	valid_map(char *argv, t_game *game, int fd)
{
	char	*line;
	int		map_flag;

	fd = open(argv, O_RDONLY);
	if (fd == -1 || !check_format(argv) || !alloc_all(game))
		return (0);
	line = get_next_line(fd);
	map_flag = 0;
	while (line != NULL)
	{
		if (!save_and_check(&map_flag, game, line))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->flag_n != 1 || game->flag_w != 1 || game->flag_e != 1
		|| game->flag_s != 1 || game->flag_f != 1 || game->flag_c != 1
		|| map_flag == 0)
		return (0);
	if (game->map->height < 3 || !check_player(game->map->grid)
		|| !check_walls(game->map->grid, game->map->height)
		|| !edit_paths(game->textures))
		return (0);
	return (1);
}
