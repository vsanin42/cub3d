/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025-02-09 19:08:29 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_header.h"

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
		while (j < ft_strlen(game->map->grid[i]))
		{
			printf("%c", game->map->grid[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}
