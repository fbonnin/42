/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:17 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:54:48 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	generate_colors(t_s *s)
{
	int i;
	int c;
	int variation;

	generate_colors_2(s);
	return ;
	i = 0;
	c = 128;
	variation = 10;
	while (i <= s->max_iterations_max)
	{
		s->colors[i] = rgb_to_int(c, c, c);
		if (c + variation < 0 || c + variation > 255)
			variation *= -1;
		c += variation;
		i++;
	}
}

void	generate_colors_2(t_s *s)
{
	int i;
	int r;
	int g;
	int b;

	i = 0;
	r = 128;
	g = 128;
	b = 128;
	while (i <= s->max_iterations_max)
	{
		s->colors[i] = rgb_to_int(r, g, b);
		move_c(s, i, &r, 0);
		move_c(s, i, &g, 1);
		move_c(s, i, &b, 2);
		i++;
	}
	s->color_set = (s->color_set + 1) % 7;
}

void	move_c(t_s *s, int i, int *c, int i_c)
{
	int shift;

	shift = 7;
	if (random_bit(s, i, i_c))
	{
		if (*c + shift < 256)
			*c += shift;
	}
	else
	{
		if (*c - shift >= 0)
			*c -= shift;
	}
}

int		random_bit(t_s *s, int i, int i_c)
{
	return ((int)(cos(i * 3 + i_c) * 1000 * pow(10, s->color_set)) % 2);
}
