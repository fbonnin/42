#include "fdf.h"

void	make_calculations(t_s *s)
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
