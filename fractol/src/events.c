/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:30 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:52:33 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	manage_events(t_s *s)
{
	mlx_expose_hook(s->window, expose_event, s);
	mlx_key_hook(s->window, keyboard_event, s);
	mlx_mouse_hook(s->window, mouse_event, s);
	mlx_hook(s->window, 6, 1 << 6, mouse_move_event, s);
	mlx_loop(s->mlx);
}

int		expose_event(t_s *s)
{
	mlx_put_image_to_window(s->mlx, s->window, s->image, 0, 0);
	return (0);
}

int		mouse_event(int button, int x, int y, t_s *s)
{
	t_point mouse;

	mouse = cell_to_point(s, x, y);
	if (button == 5 || button == 4)
	{
		s->nb_zoom++;
		if (s->nb_zoom == s->nb_zoom_max)
		{
			s->nb_zoom = 0;
			if (button == 5)
				zoom_in(s, mouse);
			else if (button == 4)
				zoom_out(s, mouse);
		}
	}
	return (0);
}

int		mouse_move_event(int x, int y, t_s *s)
{
	s->mouse_x = x;
	s->mouse_y = y;
	if (x < 0 || x >= s->width || y < 0 || y >= s->height)
		return (0);
	if (s->type == julia && s->julia_mode)
	{
		s->point_julia = cell_to_point(s, x, y);
		draw_fractal(s);
	}
	return (0);
}
