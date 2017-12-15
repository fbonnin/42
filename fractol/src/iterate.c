/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:55 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:55:16 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_point	formula(t_point z, t_point c)
{
	t_point result;

	result.x = z.x * z.x - z.y * z.y + c.x;
	result.y = 2 * z.x * z.y + c.y;
	return (result);
}

int		iterate(t_s *s, t_point point)
{
	int		nb_iterations;
	t_point	z;
	t_point	c;

	nb_iterations = 0;
	z.x = 0;
	z.y = 0;
	if (s->type == julia)
		z = point;
	c = point;
	if (s->type == julia)
		c = s->point_julia;
	while (z.x * z.x + z.y * z.y < 4 && nb_iterations < s->max_iterations)
	{
		if (s->type == burning_ship)
		{
			z.x = fabs(z.x);
			z.y = fabs(z.y);
		}
		z = formula(z, c);
		nb_iterations++;
	}
	return (nb_iterations);
}

t_point	cell_to_point(t_s *s, int x, int y)
{
	t_point point;

	point.x = s->pov.x + (x - s->width / 2) * s->cell_size;
	point.y = s->pov.y + (s->height / 2 - y) * s->cell_size;
	return (point);
}

void	fill_grid(t_s *s)
{
	int x;
	int y;

	x = 0;
	while (x < s->width)
	{
		y = 0;
		while (y < s->height)
		{
			s->grid[y][x] = iterate(s, cell_to_point(s, x, y));
			y++;
		}
		x++;
	}
}
