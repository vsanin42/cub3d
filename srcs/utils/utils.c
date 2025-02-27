/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:00:02 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/27 12:45:06 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	err(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

// gets current time from timeval struct in seconds.
// if more precision is needed, uncomment right part.
long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	// printf("get_current_time - milliseconds: %ld\n", time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time.tv_sec * 1000 + time.tv_usec / 1000); // ms
}

int	check_keymap(t_game *game)
{
	if (game->keymap.w == false && game->keymap.a == false
		&& game->keymap.s == false && game->keymap.d == false
		&& game->keymap.l == false && game->keymap.r == false)
		return (0);
	if (game->keymap.w == true)
		update_pos(game, game->dir.x, game->dir.y);
	if (game->keymap.s == true)
		update_pos(game, -game->dir.x, -game->dir.y);
	if (game->keymap.a == true)
		update_pos(game, -game->plane.x, -game->plane.y);
	if (game->keymap.d == true)
		update_pos(game, game->plane.x, game->plane.y);
	return (1);
}

// think of an int as 32 bits long sequence: 00000000 00000000 00000000 00000000
// each of those 4 bytes can represent up to 255 values.
// thanks to how RGB max value is also 255, we can encode the entire pixel in one int.
// if we have all the components, we can use: 1. bit shifting and 2. bitwise operations to combine it into one color.
// 1. << shifts the bits to the left by a specified number. when we get T component of a TRGB sequence,
// we want to position it in the first 8 bits, R component - in the bits (9 to 16), etc...
// so we shift each component by however many positions we need, b is last so it's unchanged.
// 2. bitwise OR (|) essentially merges these together and creates one color.
// 11111111 00000000 00000000 00000000 - T component after being shifted
// 00000000 11111111 00000000 00000000 - R component after being shifted
// 11111111 11111111 00000000 00000000 - T and R after bitwise OR. repeat for G and B.
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
