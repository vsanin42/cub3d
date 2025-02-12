/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025-02-09 19:08:29 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			return (0);
		i++;
	}
	if (game->floor_color[0] > 255 || game->floor_color[1] > 255
		|| game->floor_color[2] > 255 || counter != 2 || j != 3)
		return (0);
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
			return (0);
		i++;
	}
	if (game->ceiling_color[0] > 255 || game->ceiling_color[1] > 255
		|| game->ceiling_color[2] > 255 || counter != 2 || j != 3)
		return (0);
	return (1);
}
