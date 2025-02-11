/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025-02-09 19:09:29 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

int	check_char_validity(t_map_data *data, int i, int j)
{
	char	c;

	c = data->map[i][j];
	if (!is_valid_char(c))
	{
		printf("Invalid character at position [%d, %d] |%c|\n", i, j, c);
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
			printf("Open area detected at position [%d, %d]\n", i, j);
			return (0);
		}
	}
	return (1);
}

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
		while (j < (int)ft_strlen(data->map[i]))
		{
			if (!check_char_validity(data, i, j)
				|| !check_area_closure(data, i, j))
			{
				free_map_data(data);
				return (0);
			}
			j++;
		}
		i++;
	}
	free_map_data(data);
	return (1);
}

int	check_format(char *argv)
{
	int	i;

	i = 0;
	if (ft_strlen(argv) <= 4)
		return (0);
	while (argv[i])
	{
		if (!((argv[i] >= '0' && argv[i] <= '9') || (argv[i] >= 'a'
					&& argv[i] <= 'z') || (argv[i] >= 'A' && argv[i] <= 'Z')
				|| argv[i] == '.' || argv[i] == '-'
				|| argv[i] == '_' || argv[i] == '/'))
			return (0);
		if (argv[i + 1] != 0 && argv[i] == 'b' && argv[i - 1] == 'u'
			&& argv[i - 2] == 'c' && argv[i - 3] == '.')
			return (0);
		if (!argv[i + 1] && argv[i] == 'b' && argv[i - 1] == 'u'
			&& argv[i - 2] == 'c' && argv[i - 3] == '.')
			return (1);
		i++;
	}
	return (0);
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
