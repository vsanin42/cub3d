/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olomova <olomova@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025-02-09 19:09:29 by olomova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_HEADER_H
# define MY_HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

typedef struct s_map_data
{
	char	**map;
	int		rows;
	int		**visited;
}	t_map_data;

typedef struct s_map
{
	char	**grid;
	int		height;
}	t_map;

typedef struct s_game
{
	t_map	*map;
	char	**textures;
	int		*floor_color;
	int		*ceiling_color;
	int		flag_n;
	int		flag_e;
	int		flag_w;
	int		flag_s;
	int		flag_f;
	int		flag_c;
}	t_game;

int			if_direction_p2(char *line, t_game *game, int offset);
int			if_direction_p1(char *line, t_game *game, int offset);
int			if_line_1(char *line, t_game *game, int *map_flag);
int			if_surface(char *line, t_game *game, int offset);
int			if_map(char *line, t_game *game, int *map_flag, int offset);
void		parse_color_component_floor(t_game *game,
				int *j, int *i, char *line);
void		parse_color_component(t_game *game, int *j, int *i, char *line);
int			save_color_floor(char *line, t_game *game, int counter, int j);
int			save_color(char *line, t_game *game, int counter, int j);
int			err(char *text_err);
void		set_array_as_null(char **textures, int *floor_color,
				int *ceiling_color);
void		free_game(t_game *game);
void		free_map(t_map *map);
int			is_out_of_bounds(char **map, int x, int y, int rows);
t_map_data	*init_map_data(char **map, int rows);
void		free_map_data(t_map_data *data);
int			check_char_validity(t_map_data *data, int i, int j);
int			check_area_closure(t_map_data *data, int i, int j);
int			check_player(char **grid);
int			flood_fill(t_map_data *data, int x, int y);
int			check_walls(char **map, int rows);
int			check_format(char *argv);
void		flag_init(t_game *game);
void		print_colors(t_game *game);
void		print_textures(t_game *game);
void		print_map(t_game *game);
char		*ft_strdup_without_newline(const char *str);
int			add_map_line(t_map *map, const char *line);
int			is_valid_char(char c);
int			my_isspace(char c);
void		trim_spaces(char *str);
int			skip_whitespace(const char *str);
int			edit_paths(char **textures);
int			alloc_all(t_game *game);
int			save_and_check(int *map_flag, t_game *game, char *line);
int			valid_map(char *argv, t_game *game, int fd);

#endif
