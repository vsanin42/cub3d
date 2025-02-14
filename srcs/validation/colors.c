/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/14 17:44:15 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_color_component_floor(t_game *game, int *j, int *i, char *line)
{
	game->floor_color[*j] = ft_atoi(&line[*i]);
	while (line[*i] <= '9' && line[*i] >= '0')
		(*i)++;
	(*j)++;
}

void	parse_color_component(t_game *game, int *j, int *i, char *line)
{
	game->ceiling_color[*j] = ft_atoi(&line[*i]);
	while (line[*i] <= '9' && line[*i] >= '0')
		(*i)++;
	(*j)++;
}

int	save_color_floor(char *line, t_game *game, int counter, int j)
{
	int	i;

	i = 2;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			i++;
		if (line[i] <= '9' && line[i] >= '0')
			parse_color_component_floor(game, &j, &i, line);
		if (line[i] == '\n')
			break ;
		if (line[i] == ',')
			counter++;
		else
			return (err("Error: Non-numeric/negative floor RGB value!"), 0);
		i++;
	}
	if (counter != 2 || j != 3 || !check_rgb_values(game, 2))
		return (err("Error: Invalid/missing floor RGB value!"), 0);
	return (1);
}

int	save_color(char *line, t_game *game, int counter, int j)
{
	int	i;

	i = 2;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			i++;
		if (line[i] <= '9' && line[i] >= '0')
			parse_color_component(game, &j, &i, line);
		if (line[i] == '\n')
			break ;
		if (line[i] == ',')
			counter++;
		else
			return (err("Error: Non-numeric/negative ceiling RGB value!"), 0);
		i++;
	}
	if (counter != 2 || j != 3 || !check_rgb_values(game, 1))
		return (err("Error: Invalid/missing ceiling RGB value!"), 0);
	return (1);
}

int	check_rgb_values(t_game *game, int flag)
{
	if (flag == 1)
	{
		if (game->ceiling_color[0] < 0 || game->ceiling_color[0] > 255
			|| game->ceiling_color[1] < 0 || game->ceiling_color[1] > 255
			|| game->ceiling_color[2] < 0 || game->ceiling_color[2] > 255)
			return (0);
	}
	else if (flag == 2)
	{
		if (game->floor_color[0] < 0 || game->floor_color[0] > 255
			|| game->floor_color[1] < 0 || game->floor_color[1] > 255
			|| game->floor_color[2] < 0 || game->floor_color[2] > 255)
			return (0);
	}
	return (1);
}
