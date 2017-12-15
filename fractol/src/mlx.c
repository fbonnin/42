/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:53:21 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:53:22 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		rgb_to_int(int r, int g, int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

void	put_pixel_to_image(void *image, int x, int y, int color)
{
	int *pixels;
	int bits_per_pixel;
	int size_line;
	int endian;

	pixels = (int *)mlx_get_data_addr(image,
	&bits_per_pixel, &size_line, &endian);
	pixels[y * size_line / 4 + x] = color;
}
