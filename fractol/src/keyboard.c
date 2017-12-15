/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:53:01 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:53:02 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		keyboard_event(int key, t_s *s)
{
	if (key == 51)
		init_display(s);
	else if (key >= 123 && key <= 126)
		arrow(key, s);
	else if (key == 69 || key == 78)
		change_max_iterations(key, s);
	else if (key == 49)
		s->julia_mode = 0;
	else if (key == 257)
	{
		generate_colors(s);
		draw_fractal(s);
	}
	else if (key == 53)
		end(s);
	return (0);
}

void	arrow(int key, t_s *s)
{
	if (key == 123)
		s->pov.x -= s->width * s->cell_size * s->arrows_speed;
	else if (key == 124)
		s->pov.x += s->width * s->cell_size * s->arrows_speed;
	else if (key == 125)
		s->pov.y -= s->height * s->cell_size * s->arrows_speed;
	else
		s->pov.y += s->height * s->cell_size * s->arrows_speed;
	draw_fractal(s);
}

void	change_max_iterations(int key, t_s *s)
{
	if (key == 69)
	{
		s->max_iterations += s->max_iterations_speed;
		if (s->max_iterations > s->max_iterations_max)
			s->max_iterations = s->max_iterations_max;
	}
	else
	{
		s->max_iterations -= s->max_iterations_speed;
		if (s->max_iterations < 0)
			s->max_iterations = 0;
	}
	draw_fractal(s);
}
