void    find_position3(t_s *s)
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

void	find_position3_2(t_s *s)
{
	int row;
	int col;

	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->points[row][col].position3.x = s->points[row][col].position2.x;
			if (s->pov.z < 0)
				s->points[row][col].position3.x *= -1;
			s->points[row][col].position3.y = s->points[row][col].position2.y;
			col++;
		}
		row++;
	}
}

void	find_max_position3(t_s *s)
{
	int row;
	int col;

	s->max_x3 = 0;
	s->max_y3 = 0;
	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->max_x3 = fmax(s->max_x3, fabs(s->points[row][col].position3.x));
			s->max_y3 = fmax(s->max_y3, fabs(s->points[row][col].position3.y));
			col++;
		}
		row++;
	}
}

void	find_position4(t_s *s)
{
	double m;
	int row;
	int col;

	m = fmin(s->width / (s->max_x3 * 2), s->height / (s->max_y3 * 2));
	row = 0;
	while (row < s->nb_rows)
	{
		col = 0;
		while (col < s->nb_cols)
		{
			s->points[row][col].position4.x = (double)s->width / 2 + m * s->points[row][col].position3.x;
			if (s->points[row][col].position4.x == s->width)
				s->points[row][col].position4.x--;
			s->points[row][col].position4.y = (double)s->height / 2 - m * s->points[row][col].position3.y;
			if (s->points[row][col].position4.y == s->height)
				s->points[row][col].position4.y--;
			col++;
		}
		row++;
	}
}
