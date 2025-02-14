/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/14 18:49:58 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

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
	void	*mlx;
	void	*win;
}	t_game;

typedef struct s_win_params
{
	void	*mlx;
	void	*win;
	t_game	*game;
}	t_win_params;

typedef struct s_map_data
{
	char	**map;
	int		rows;
	int		**visited;
}	t_map_data;

/* srcs/utils */
/* srcs/utils/print.c */
void		print_colors(t_game *game);
void		print_textures(t_game *game);
void		print_map(t_game *game);

/* srcs/utils/utils.c */
int			err(char *text_err);
void		free_game(t_game *game);
void		free_map(t_map *map);

/* ------------------------------------------------ */

/* srcs/validation */
/* srcs/validation/colors.c */
int			check_rgb_values(t_game *game, int flag);
int			save_color_floor(char *line, t_game *game, int counter, int j);
int			save_color(char *line, t_game *game, int counter, int j);
void		parse_color_component(t_game *game, int *j, int *i, char *line);
void		parse_color_component_floor(t_game *game,
				int *j, int *i, char *line);

/* srcs/validation/map_check.c */
int			is_out_of_bounds(char **map, int x, int y, int rows);
int			flood_fill(t_map_data *data, int x, int y);
t_map_data	*init_map_data(char **map, int rows);
void		free_map_data(t_map_data *data, int index);
int			check_player(char **grid);

/* srcs/validation/map_check2.c */
int			check_char_validity(t_map_data *data, int i, int j);
int			check_area_closure(t_map_data *data, int i, int j);
int			check_walls(char **map, int rows);
int			check_format(char *argv, int fd);
void		flag_init(t_game *game);

/* srcs/validation/map_elements.c */
int			if_direction_p2(char *line, t_game *game, int offset);
int			if_direction_p1(char *line, t_game *game, int offset);
int			if_line_1(char *line, t_game *game, int *map_flag);
int			if_surface(char *line, t_game *game, int offset);
int			if_map(char *line, t_game *game, int *map_flag, int offset);

/* srcs/validation/string_funct.c */
char		*ft_strdup_without_newline(const char *str);
int			add_map_line(t_map *map, const char *line);
int			is_valid_char(char c);
int			my_isspace(char c); // not used
char		*trim_spaces(char *str); // not used

// could have one less file if rearranged between these three files ^v

/* srcs/validation/string_funct2.c */
char		*trim_wrapper(char *str);
int			skip_whitespace(const char *str);
int			edit_paths(char **textures);
int			check_texture_path(char *str);

/* srcs/validation/valid_map.c */
int			alloc_all(t_game *game, int fd);
int			save_and_check(int *map_flag, t_game *game, char *line);
int			check_fd(int fd);
int			check_height(int height);
int			valid_map(char *argv, t_game *game, int fd);

/* ------------------------------------------------ */

/* srcs/start_game.c */
void		err_exit(char *err_msg, t_game *game); // not used
int			close_window(t_game *game);
int			key_press(int keycode, t_game *game);
int			start_game(t_game *game);
int			render(t_game *game);

/* srcs/main.c */
int			alloc_and_nullify(t_game *game);

void		set_array_as_null(char **textures, int *floor_color,
				int *ceiling_color); // not used

#endif
