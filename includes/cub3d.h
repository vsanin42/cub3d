/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/02/19 19:19:54 by vsanin           ###   ########.fr       */
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
# include <sys/time.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_map
{
	char	**grid;
	int		height;
}	t_map;

typedef enum s_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_side;

typedef enum s_trgb
{
	TRANSPARENT,
	RED,
	GREEN,
	BLUE
}	t_trgb;

// struct to hold all variables used in raycasting
typedef struct s_ray
{
	double	camera_x; 		// x coordinate in the camera plane
	double	ray_dir_x;		// direction of a ray
	double	ray_dir_y;
	double	side_dist_x;	// distance to the first x/y side from current position
	double	side_dist_y;
	double	delta_dist_x;	// distance from one x/y side to the next
	double	delta_dist_y;
	double	perp_wall_dist;	// distance from camera plane to the wall - to make all rays the same length - avoids fisheye effect
	double	wall_x;			// where exactly the wall was hit (between 0 and 1 value)
	double	draw_step;		// scaling variable to tell how many pixels on the texture correspond to one pixel on the screen
	double	tex_pos;		// starting drawing position of the texture
	int		tex_x;			// how does wall_x map onto the texture - wall_x scaled to TEX_WIDTH
	int		tex_y;			// y coordinate of the texture
	int		map_x;			// map square coordinates (not the position inside the square - so just int)
	int		map_y;
	int		step_x;			// in which direction to step (-1/1)
	int		step_y;
	int		hit;			// was wall hit or not - DDA stopping condition
	int		side;			// which side was hit - y or x
	int		line_height;	// height of the vertical line to be drawn - depends on perp_wall_dist
	int		draw_start;		// where to start and stop drawing the line - lowest/highest points in a vertical column
	int		draw_end;
	t_side	nswe;			// which exact side was hit - NSWE 0123 like the textures array.
}	t_ray;

// this struct holds all the info related to an image in one place
typedef struct s_image
{
	void		*ptr; // pointer to the image
	int			*addr; // was char*, changed to int* to better navigate to pixels. // address of the image and related information 
	int			bpp; // next 3 aren't currently used but need to exist for parameters of mlx_get_data_addr 
	int			size_line;
	int			endian;
	int			w;
	int			h;
}	t_image;

typedef struct s_game
{
	t_map	*map;	// validation
	char	**textures;
	int		*floor_color;
	int		*ceiling_color;
	int		flag_n;
	int		flag_e;
	int		flag_w;
	int		flag_s;
	int		flag_f;
	int		flag_c;
	t_pos	pos;	// raycasting
	t_pos	dir;
	t_pos	plane;
	double	time;
	double	old_time;
	double	frame_time;
	void	*mlx;	// mlx
	void	*win;
	t_image img;
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
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

/* srcs/raycasting */
/* srcs/raycasting/raycaster.c */
int			render(t_game *game);
void		dda(t_ray *r, t_game *game);

/* srcs/raycasting/setters.c */
void		set_ray_variables(t_ray *r, t_game *game, int x);
void		set_step_and_side(t_ray *r, t_game *game);
void		set_final_vars(t_ray *r, t_game *game);
void		set_hit_and_nswe(t_ray *r);
void		set_frame_time(t_game *game);

/* srcs/raycasting/TODOOOOOOOOOOOO */

/* ------------------------------------------------ */

/* srcs/utils */
/* srcs/utils/print.c */
void		print_colors(t_game *game);
void		print_textures(t_game *game);
void		print_map(t_game *game);

/* srcs/utils/utils.c */
int			err(char *text_err);
long		get_current_time(void);
long		get_timestamp(long start); // not used, maybe will be

/* srcs/utils/free.c */
void		free_game(t_game *game);
void		free_map(t_map *map);
void		free_map_data(t_map_data *data, int index);

/* srcs/utils/rgb.c */
int			create_trgb(int t, int r, int g, int b);
int			get_trgb(int trgb, t_trgb mode);

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
void		set_start_pos(char c, int i, int j, t_game *game);
int			check_player(char **grid, t_game *game);

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
void		load_textures(t_game *game);

/* srcs/main.c */
int			alloc_and_nullify(t_game *game);

void		set_array_as_null(char **textures, int *floor_color,
				int *ceiling_color); // not used

#endif
