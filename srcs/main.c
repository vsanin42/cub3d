/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:52:15 by olomova           #+#    #+#             */
/*   Updated: 2025/03/02 18:28:45 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// validate map by checking:
// - map file existence/permissions/extension
// - check the file line by line for all necessary elements (textures/F/C/map).
// error if mismatch in element count.
// error if area too small, unclosed, no/extra player position,
// problem with texture path...
int	valid_map(char *argv, t_game *game, int fd)
{
	char	*line;
	int		map_flag;

	fd = open(argv, O_RDONLY); 
	if (check_fd(fd) == -1 || !check_format(argv, fd) || !alloc_all(game, fd)) // + close(fd) inside both if error
		return (0);
	line = get_next_line(fd);
	map_flag = 0;
	while (line != NULL)
	{
		if (!save_and_check(&map_flag, game, line))
			return (close(fd), 0); // + close(fd)
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->flag_n != 1 || game->flag_w != 1 || game->flag_e != 1
		|| game->flag_s != 1 || game->flag_f != 1 || game->flag_c != 1
		|| map_flag == 0) // is map_flag == 0 enough to check? 
		return (err("Error: Missing/extra textures, colors and/or map!"), 0);
	if (!check_height(game->map->height) || !check_player(game->map->grid, game)
		|| !check_walls(game->map->grid, game->map->height)
		|| !edit_paths(game->textures))
		return (0);
	return (1);
}

// 1. initialize the mlx, window and main image instances.
// 2. save the image address and other info in addr - needed to draw on pixels.
// 3. load textures from paths specified in textures array.
// 4. hook into key press, key release and close window events.
// 5. hook into render function as the main mlx loop function + start the loop.
int	start_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (err("Error: mlx_init() failed!:("), 0);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		return (free(game->mlx), err("Error: mlx_new_window() failed!:("), 0);
	game->img.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img.addr = (int *)mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.size_line, &game->img.endian);
	load_textures(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->win, EnterNotify, EnterWindowMask, mouse_enter, game);
	mlx_hook(game->win, LeaveNotify, LeaveWindowMask, mouse_leave, game);
	mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, close_window, game); // 1L << 0
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
	return (1);
}

// 1. zero out the game struct for convenience later.
// 2. check argc, if OK - allocate the key members for validation.
// 3. check map validity.
// 4. start game - load textures, setup and run mlx...
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (err("Error: Too few or many arguments!"));
	if (alloc_and_nullify(&game) == 1)
		return (1);
	if (!valid_map(argv[1], &game, 0))
		return (free_game(&game), err("Error: Map validation failed!:("));
	// print_textures(&game);
	// print_colors(&game);
	// print_map(&game);
	if (!start_game(&game))
		return (free_game(&game), 1);
	free_game(&game);
	return (0);
}
