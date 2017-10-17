/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:34:43 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/18 16:34:46 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			make_calculations(t_s *s)
{
	find_position1(s);
	find_position2(s);
	find_u(s);
	find_v(s);
	if (s->pov.x == 0 && s->pov.y == 0)
		find_position3_2(s);
	else
		find_position3(s);
	find_max_position3(s);
	find_position4(s);
}

void			find_position1(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->points[row][col].position1.x =
			col - (double)(s->nb_cols - 1) / 2;
			s->points[row][col].position1.y =
			-row + (double)(s->nb_rows - 1) / 2;
			col++;
		}
		row++;
	}
}

t_xyz_double	find_projection(t_s *s, t_xyz_double position)
{
	t_xyz_double	result;
	double			k;

	k = 1 -
	(s->pov.x * position.x + s->pov.y * position.y + s->pov.z * position.z) /
	(pow(s->pov.x, 2) + pow(s->pov.y, 2) + pow(s->pov.z, 2));
	result.x = position.x + k * s->pov.x;
	result.y = position.y + k * s->pov.y;
	result.z = position.z + k * s->pov.z;
	return (result);
}

void			find_position2(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->points[row][col].position2 =
			find_projection(s, s->points[row][col].position1);
			col++;
		}
		row++;
	}
}

void			find_u(t_s *s)
{
	if (s->pov.x == 0 && s->pov.y == 0)
	{
		if (s->pov.z > 0)
			s->u.x = 1;
		else
			s->u.x = -1;
		s->u.y = 0;
		s->u.z = 0;
		return ;
	}
	s->u.x = -s->pov.y;
	s->u.y = s->pov.x;
	s->u.z = 0;
	s->u = normalize(s->u);
}
