/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:08:29 by olomova           #+#    #+#             */
/*   Updated: 2025/03/06 15:49:21 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOUSE_SENSITIVITY 0.0075
# define RED 16711680

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

typedef struct s_mimap
{
	int		map_side;
	int		offset;
	int		y_start;
	int		x_start;
	int		y_win;
	int		x_win;
	int		y_step_count;
	int		x_step_count;
	int		g_y;
	int		g_x;
	double	pos_y;
	double	pos_x;
	double	step;
}	t_mimap;

typedef enum s_side
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}	t_side;

// struct to hold all variables used in raycasting.
// camera_x:		x coordinate in the camera plane
// ray_dir_x: 		direction of a ray
// side_dist_x: 	distance to the first x/y side from current position
// delta_dist_x: 	distance from one x/y side to the next
// perp_wall_dist:	distance from camera plane to the wall
// 					- to make all rays the same length - avoids fisheye effect
// wall_x: 			where exactly the wall was hit (between 0 and 1 value)
// draw_step:		scaling variable - how many pixels on the texture
// 					correspond to one pixel on the screen
// tex_pos:			starting drawing position of the texture
// tex_x;			how wall_x maps onto texture - wall_x scaled to TEX_WIDTH
// tex_y;			y coordinate of the texture
// map_x;			map square coordinates (not the position inside the square)
// step_x;			in which direction to step (-1/1)
// hit;				was wall hit or not - DDA stopping condition
// side;			which side was hit - y or x
// line_height;		height of the line to be drawn - depends on perp_wall_dist
// draw_start;		where to start and stop drawing the line
// 					- lowest/highest points in a vertical column
// nswe;			which exact side was hit (NSWE 0123 like the textures array)
typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	double	draw_step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_side	nswe;
}	t_ray;

// this struct holds all the info related to an image in one place
// ptr: pointer to the image
// addr: was char*, changed to int* to better navigate to pixels.
// address of the image and related information.
// next 3 aren't used but must exist for parameters of mlx_get_data_addr.
typedef struct s_image
{
	void	*ptr;
	int		*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		w;
	int		h;
}	t_image;

typedef struct s_kmap
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l;
	bool	r;
}	t_kmap;

typedef struct s_game
{
	t_map	*map;
	char	**textures;
	int		*floor_color;
	int		*ceiling_color;
	int		floor;
	int		ceiling;
	int		flag_n;
	int		flag_e;
	int		flag_w;
	int		flag_s;
	int		flag_f;
	int		flag_c;
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
	double	time;
	double	old_time;
	double	frame_time;
	double	move_speed;
	double	rot_speed;
	void	*mlx;
	void	*win;
	t_image	img;
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
	t_kmap	keymap;
	t_pos	mouse;
	bool	mouse_in_window;
}	t_game;

typedef struct s_map_data
{
	char	**map;
	int		rows;
	int		**visited;
}	t_map_data;

/* -------------------------------------------------------------------------- */
/*								     GAME							   	  	  */
/* -------------------------------------------------------------------------- */

/* srcs/game/events.c */
int			close_window(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			update_pos(t_game *game, double x, double y);
int			update_cam(t_game *game);

/* srcs/game/minimap_init.c */
void		draw_map_square(t_game *game, t_mimap *minimap);
void		draw_map_padding_horizontal(t_game *game, t_mimap *minimap);
void		draw_map_padding_vertical(t_game *game, t_mimap *minimap);
void		draw_map_padding_horizontal2(t_game *game, t_mimap *minimap);
void		draw_map_padding_vertical2(t_game *game, t_mimap *minimap);

/* srcs/game/minimap.c */
void		draw_map_top_right(t_game *game, t_mimap *m);
void		draw_map_top_left(t_game *game, t_mimap *m);
void		draw_map_bottom_right(t_game *game, t_mimap *m);
void		draw_map_bottom_left(t_game *game, t_mimap *m);
void		draw_minimap(t_game *game);

/* srcs/game/mouse.c */
int			mouse_enter(t_game *game);
int			mouse_leave(t_game *game);
int			mouse_move(int x, int y, t_game *game);
int			update_mouse_cam(t_game *game);
void		rotation_matrix(t_game *game, double angle);

/* srcs/game/raycasting.c */
void		dda(t_ray *r, t_game *game);
void		set_ray_variables(t_ray *r, t_game *game, int x);
void		set_step_and_side(t_ray *r, t_game *game);
void		set_final_vars(t_ray *r, t_game *game);
void		set_hit_and_nswe(t_ray *r);

/* srcs/game/game_utils.c */
void		set_frame_time(t_game *game);
t_image		*get_nswe_tex(t_game *game, t_side nswe);
int			load_textures(t_game *game);
int			is_floor(t_game *game, int g_y, int g_x);
void		draw_red_dot(t_game *game, t_mimap *minimap);

/* srcs/game/render.c */
int			render(t_game *game);
void		draw_line(t_ray *r, t_game *game, int x);
void		draw_ceiling(t_ray *r, t_game *game, int x);
void		draw_floor(t_ray *r, t_game *game, int x);
void		move(t_game *game);

/* -------------------------------------------------------------------------- */
/*									UTILS							     	  */
/* -------------------------------------------------------------------------- */

/* srcs/utils/print.c */ // this is not used at all so delete later completely
void		print_colors(t_game *game);
void		print_textures(t_game *game);
void		print_map(t_game *game);

/* srcs/utils/utils.c */
int			err(char *text_err);
long		get_current_time(void);
int			create_trgb(int t, int r, int g, int b);
int			check_texture_size(t_game *game);

/* srcs/utils/free.c */
void		free_game(t_game *game);
void		free_map(t_map *map);
void		free_map_data(t_map_data *data, int index);
int			alloc_and_nullify(t_game *game);
int			alloc_all(t_game *game, int fd);

/* -------------------------------------------------------------------------- */
/*								 VALIDATION							   	  	  */
/* -------------------------------------------------------------------------- */

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

/* srcs/validation/string_ft.c */
char		*trim_wrapper(char *str);
int			edit_paths(char **textures);
int			check_texture_path(char *str);
char		*ft_strdup_without_newline(const char *str);
int			add_map_line(t_map *map, const char *line);

/* srcs/validation/valid_utils.c */
int			save_and_check(int *map_flag, t_game *game, char *line);
int			check_fd(int fd);
int			check_height(int height);
int			is_valid_char(char c);
int			skip_whitespace(const char *str);

/* -------------------------------------------------------------------------- */
/*								    MAIN							   	  	  */
/* -------------------------------------------------------------------------- */

/* srcs/main.c */
int			valid_map(char *argv, t_game *game, int fd);
int			start_game(t_game *game);

#endif
