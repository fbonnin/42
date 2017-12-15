/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:53:26 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:53:28 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_s *s, t_point mouse)
{
	double shift;

	shift = s->width / 2 * s->cell_size * (1 - s->zoom_speed);
	if (fabs(mouse.x - s->pov.x) <= shift)
		s->pov.x = mouse.x;
	else if (mouse.x > s->pov.x)
		s->pov.x += shift;
	else
		s->pov.x -= shift;
	shift = s->height / 2 * s->cell_size * (1 - s->zoom_speed);
	if (fabs(mouse.y - s->pov.y) <= shift)
		s->pov.y = mouse.y;
	else if (mouse.y > s->pov.y)
		s->pov.y += shift;
	else
		s->pov.y -= shift;
	s->cell_size *= s->zoom_speed;
	draw_fractal(s);
}

void	zoom_out(t_s *s, t_point mouse)
{
	double shift;

	shift = s->width / 2 * s->cell_size * (1 / s->zoom_speed - 1);
	if (fabs(mouse.x - s->pov.x) <= shift)
		s->pov.x = mouse.x;
	else if (mouse.x > s->pov.x)
		s->pov.x += shift;
	else
		s->pov.x -= shift;
	shift = s->height / 2 * s->cell_size * (1 / s->zoom_speed - 1);
	if (fabs(mouse.y - s->pov.y) <= shift)
		s->pov.y = mouse.y;
	else if (mouse.y > s->pov.y)
		s->pov.y += shift;
	else
		s->pov.y -= shift;
	s->cell_size /= s->zoom_speed;
	draw_fractal(s);
}
