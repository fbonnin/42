#include "fdf.h"

void	find_position1(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->points[row][col].position1.x = col - (double)(s->nb_cols - 1) / 2;
			s->points[row][col].position1.y = -row + (double)(s->nb_rows - 1) / 2;
			col++;
		}
		row++;
	}
}

void	find_position2(t_s *s)
{
	int		row;
	int		col;
	double	k;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			k = 1 - (
			s->pov.x * s->points[row][col].position1.x +
			s->pov.y * s->points[row][col].position1.y +
			s->pov.z * s->points[row][col].position1.z) /
			(pow(s->pov.x, 2) + pow(s->pov.y, 2) + pow(s->pov.z, 2));
			
			s->points[row][col].position2.x =
			s->points[row][col].position1.x + k * s->pov.x;
			s->points[row][col].position2.y =
			s->points[row][col].position1.y + k * s->pov.y;
			s->points[row][col].position2.z =
			s->points[row][col].position1.z + k * s->pov.z;
			col++;
		}
		row++;
	}
}

void	find_u(t_s *s)
{
	if (s->pov.x == 0 && s->pov.y == 0)
	{
		if (s->pov.z > 0)
			s->u = {1, 0, 0};
		else
			s->u = {-1, 0, 0};
		return ;
	}
	s->u = {-s->pov.y, s->pov.x, 0};
	s->u = normalize(s->u);
}

void	find_v(t_s *s)
{
	t_xyz vector_pov_i;

	if (s->pov.x == 0 && s->pov.y == 0)
	{
		s->v = {0, 1, 0};
		return ;
	}
	if (s->pov.z > -1 && s->pov.z < 1)
	{
		s->pov.z = 0;
		s->v = {0, 0, 1};
		return ;
	}
	vector_pov_i = {-s->pov.x, -s->pov.y, (pow(s->pov.x, 2) + pow(s->pov.y, 2)) / s->pov.z};
	s->v = normalize(vector_pov_i);
	if (s->pov.z < 0)
	{
		s->v.x *= -1;
		s->v.y *= -1;
		s->v.z *= -1;
	}
}

void	find_position3(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->points[row][col].position3.y =
			(s->points[row][col].position2.z - s->pov.z) / s->v.z;
			if (s->u.x != 0)
				s->points[row][col].position3.x =
				(s->points[row][col].position2.x - s->pov.x -
				s->points[row][col].position3.y * s->v.x) / s->u.x;
			else
				s->points[row][col].position3.x =
				(s->points[row][col].position2.y - s->pov.y -
				s->points[row][col].position3.y * s->v.y) / s->u.y;
			col++;
		}
		row++;
	}
}
