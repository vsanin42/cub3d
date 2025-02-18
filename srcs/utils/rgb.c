/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanin <vsanin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:40:55 by vsanin            #+#    #+#             */
/*   Updated: 2025/02/18 17:11:53 by vsanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// these functions will be used to get TRGB value of a pixel on the texture.
// having all of the components needed to create a color, it can then be created again to be printed onto a new frame.

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

// does the opposite by extracting each value by moving it to the last 8 bits.
// 11111111 00000000 00000000 00000000 - T component before being shifted
// 00000000 00000000 00000000 11111111 - T component after being shifted (this is actually the same as 0xFF)
// bitwise AND checks all bits, if both are 1 - leave 1, otherwise leave 0.
// this makes sure that all bits to the left of these last 8 bits are 0 and will not matter
// while the 8 bits at the end are returned.
// 11110000 10101001 10101010 10100101 - TRGB
// ...
// 00000000 00000000 00000000 11110000 - after T shift
// 00000000 00000000 00000000 11111111 - 0xFF
// now all pairs of 00, 01 and 10 become 0, while pairs of 11 stay 1. result:
// 00000000 00000000 00000000 11110000 
int	get_trgb(int trgb, t_trgb mode)
{
	if (mode == TRANSPARENT)
		return ((trgb >> 24) & 0xFF);
	if (mode == RED)
		return ((trgb >> 16) & 0xFF);
	if (mode == GREEN)
		return ((trgb >> 8) & 0xFF);
	if (mode == BLUE)
		return (trgb & 0xFF);
}
