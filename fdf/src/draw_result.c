/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:35:23 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/18 16:39:24 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_result(t_s *s)
{
	draw_segments(s);
}

void	draw_segments(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			if (col < s->nb_cols - 1)
				draw_segment(s, s->points[row][col].position4,
				s->points[row][col + 1].position4);
			if (row < s->nb_rows - 1)
				draw_segment(s, s->points[row][col].position4,
				s->points[row + 1][col].position4);
			col++;
		}
		row++;
	}
}

void	draw_segment(t_s *s, t_xy_int p1, t_xy_int p2)
{
	t_xy_double pixel1;
	t_xy_double pixel2;

	pixel1.x = (double)p1.x + 0.5;
	pixel1.y = (double)p1.y + 0.5;
	pixel2.x = (double)p2.x + 0.5;
	pixel2.y = (double)p2.y + 0.5;
	if (p1.x == p2.x && p1.y == p2.y)
		put_pixel_to_image(s->image, p1.x, p1.y, s->color);
	else if (abs(p1.x - p2.x) > abs(p1.y - p2.y))
		draw_segment_horizontal(s, pixel1, pixel2);
	else
		draw_segment_vertical(s, pixel1, pixel2);
}

void	draw_segment_horizontal(t_s *s, t_xy_double pixel1, t_xy_double pixel2)
{
	t_xy_double	left;
	t_xy_double	right;
	double		a;
	double		b;
	double		x;

	if (pixel1.x < pixel2.x)
	{
		left = pixel1;
		right = pixel2;
	}
	else
	{
		left = pixel2;
		right = pixel1;
	}
	a = (right.y - left.y) / (right.x - left.x);
	b = pixel1.y - a * pixel1.x;
	x = left.x;
	while (x <= right.x)
	{
		put_pixel_to_image(s->image, x, a * x + b, s->color);
		x++;
	}
}

void	draw_segment_vertical(t_s *s, t_xy_double pixel1, t_xy_double pixel2)
{
	t_xy_double	top;
	t_xy_double	bottom;
	double		a;
	double		b;
	double		y;

	if (pixel1.y < pixel2.y)
	{
		top = pixel1;
		bottom = pixel2;
	}
	else
	{
		top = pixel2;
		bottom = pixel1;
	}
	a = (bottom.x - top.x) / (bottom.y - top.y);
	b = pixel1.x - a * pixel1.y;
	y = top.y;
	while (y <= bottom.y)
	{
		put_pixel_to_image(s->image, a * y + b, y, s->color);
		y++;
	}
}
