/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:22:39 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/21 15:34:05 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// get_next_line(-1) cleans whatever remains in the buffer
// if stopped reading in the middle of file
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

int	check_height(int height)
{
	if (height < 3)
		return (err("Error: The map is too small!"), 0);
	return (1);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == 'D');
}

int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	return (i);
}
