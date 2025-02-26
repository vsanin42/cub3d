/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:43:02 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/26 12:38:14 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// set time and old_time to determine fps once the whole image is drawn
void	set_frame_time(t_game *game)
{
	game->old_time = game->time;
	game->time = get_current_time(); // returns seconds (in long), might need more precision
	game->frame_time = (game->time - game->old_time) / (double)1000;
	// there is currently a problem with fps counting idk. look into it again
	printf("FPS: %.0f\n", 1 / game->frame_time); // optional?
}

// gets the correct texture depending on the side that was hit
t_image	*get_nswe_tex(t_game *game, t_side nswe)
{
	if (nswe == NORTH)
		return (&game->north);
	if (nswe == SOUTH)
		return (&game->south);
	if (nswe == WEST)
		return (&game->west);
	if (nswe == EAST)
		return (&game->east);
	return (NULL);
}
