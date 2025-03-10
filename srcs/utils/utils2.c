/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:44:44 by vsanin            #+#    #+#             */
/*   Updated: 2025/03/10 10:20:16 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_colors(t_game *game)
{
	printf("Floor Color (RGB): %d, %d, %d\n", game->floor_color[0],
		game->floor_color[1], game->floor_color[2]);
	printf("Ceiling Color (RGB): %d, %d, %d\n", game->ceiling_color[0],
		game->ceiling_color[1], game->ceiling_color[2]);
}

void	print_textures(t_game *game)
{
	printf("Textures:\n");
	printf("North Texture: %s\n", game->textures[0]);
	printf("South Texture: %s\n", game->textures[1]);
	printf("West Texture: %s\n", game->textures[2]);
	printf("East Texture: %s\n", game->textures[3]);
}

void	print_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	printf("Map:\n");
	while (i < game->map->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map->grid[i]))
		{
			printf("%c", game->map->grid[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	respawn_doors(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	if (game->door_open == true
		&& (game->map->grid[(int)game->pos.y + 1][(int)game->pos.x] != 'O'
		&& game->map->grid[(int)game->pos.y - 1][(int)game->pos.x] != 'O'
		&& game->map->grid[(int)game->pos.y][(int)game->pos.x + 1] != 'O'
		&& game->map->grid[(int)game->pos.y][(int)game->pos.x - 1] != 'O'
		&& game->map->grid[(int)game->pos.y][(int)game->pos.x] != 'O'))
	{
		while (y < game->map->height)
		{
			x = 0;
			while (x < ft_strlen(game->map->grid[y]))
			{
				if (game->map->grid[y][x] == 'O')
					game->map->grid[y][x] = 'D';
				x++;
			}
			y++;
		}
		game->door_open = false;
	}
}

// maybe * other numbers between 4 and 8
void	open_door(t_game *game, t_pos proj)
{
	if ((int)(proj.y - MOVE_STEP * 8) < 0 || (int)(proj.x - MOVE_STEP * 8) < 0
		|| (int)(proj.y + MOVE_STEP * 8) >= game->map->height
		|| (int)(proj.x + MOVE_STEP * 8) >=
		ft_strlen(game->map->grid[(int)(proj.y + MOVE_STEP * 8)]))
		return ;
	if (game->map->grid[(int)(proj.y - MOVE_STEP * 8)][(int)proj.x] == 'D')
	{
		game->map->grid[(int)(proj.y - MOVE_STEP * 8)][(int)proj.x] = 'O';
		game->door_open = true;
	}
	else if (game->map->grid[(int)(proj.y + MOVE_STEP * 8)][(int)proj.x] == 'D')
	{
		game->map->grid[(int)(proj.y + MOVE_STEP * 8)][(int)proj.x] = 'O';
		game->door_open = true;
	}
	else if (game->map->grid[(int)proj.y][(int)(proj.x - MOVE_STEP * 8)] == 'D')
	{
		game->map->grid[(int)proj.y][(int)(proj.x - MOVE_STEP * 8)] = 'O';
		game->door_open = true;
	}
	else if (game->map->grid[(int)proj.y][(int)(proj.x + MOVE_STEP * 8)] == 'D')
	{
		game->map->grid[(int)proj.y][(int)(proj.x + MOVE_STEP * 8)] = 'O';
		game->door_open = true;
	}
}
