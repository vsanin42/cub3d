/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:00:02 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/26 18:51:46 by vsanin           ###   ########.fr       */
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

// NOT USED ATM
// gets the current timestamp: elapsed time from start time and current time.
// calculated in microseconds and converted to milliseconds for the timestamp.
long	get_timestamp(long start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((((current.tv_sec * 1000000) + current.tv_usec) - start) / 1000);
}

int	check_keymap(t_game *game)
{
	if (game->keymap.w == false && game->keymap.a == false
		&& game->keymap.s == false && game->keymap.d == false
		&& game->keymap.l == false && game->keymap.r == false)
		return (0);
	return (1);
}
