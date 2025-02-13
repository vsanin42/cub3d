/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/13 18:07:59 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_char_validity(t_map_data *data, int i, int j)
{
	char	c;

	c = data->map[i][j];
	if (!is_valid_char(c))
	{
		printf("Error: invalid character at position [%d, %d] |%c|\n", i, j, c);
		return (0);
	}
	return (1);
}

int	check_area_closure(t_map_data *data, int i, int j)
{
	char	c;

	c = data->map[i][j];
	if ((c == '0' || c == 'N' || c == 'S' || c == 'E'
			|| c == 'W') && !data->visited[i][j])
	{
		if (!flood_fill(data, i, j))
		{
			printf("Error: open area detected at position [%d, %d]\n", i, j);
			return (0);
		}
	}
	return (1);
}

// map is grid
int	check_walls(char **map, int rows)
{
	int			i;
	int			j;
	t_map_data	*data;

	data = init_map_data(map, rows);
	if (!data)
		return (0);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]))
		{
			if (!check_char_validity(data, i, j)
				|| !check_area_closure(data, i, j))
			{
				free_map_data(data, -1);
				return (0);
			}
			j++;
		}
		i++;
	}
	free_map_data(data, -1);
	return (1);
}

// 1. check length: if too short, return
// 2. check extension: if wrong, return
// 3. check forbidden chars: if found return
// if everything passes, success
int	check_format(char *argv)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(argv);
	if (len <= 4)
		return (err("Error: filename is too short!"), 0);
	if (ft_strncmp(argv + len - 4, ".cub", 4) != 0) // if matches, it returns 0
		return (err("Error: wrong extension!"), 0);
	while (argv[i]) // check for non-alnum and non ._-/ characters
	{
		if (!((argv[i] >= '0' && argv[i] <= '9')
				|| (argv[i] >= 'a' && argv[i] <= 'z')
				|| (argv[i] >= 'A' && argv[i] <= 'Z')
				|| argv[i] == '.' || argv[i] == '-'
				|| argv[i] == '_' || argv[i] == '/'))
			return (err("Error: forbidden character in the filename!"), 0);
		i++;
	}
	return (1);
}

void	flag_init(t_game *game)
{
	game->flag_n = 0;
	game->flag_e = 0;
	game->flag_w = 0;
	game->flag_s = 0;
	game->flag_f = 0;
	game->flag_c = 0;
}
