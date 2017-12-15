/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:24 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:52:27 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	grid_to_image(t_s *s)
{
	int x;
	int y;

	x = 0;
	while (x < s->width)
	{
		y = 0;
		while (y < s->height)
		{
			put_pixel_to_image(s->image, x, y, s->colors[s->grid[y][x]]);
			y++;
		}
		x++;
	}
}

void	draw_fractal(t_s *s)
{
	fill_grid(s);
	grid_to_image(s);
	mlx_put_image_to_window(s->mlx, s->window, s->image, 0, 0);
}

void	init_display(t_s *s)
{
	s->pov = s->pov_init;
	s->cell_size = s->radius_init / (ft_min(s->width, s->height) / 2);
	s->max_iterations = s->max_iterations_init;
	s->point_julia = s->point_julia_init;
	s->julia_mode = 1;
	draw_fractal(s);
}
