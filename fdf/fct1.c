void	find_position1(t_point **points, int nb_rows, int nb_cols)
{
	int row;
	int col;

	row = 0;
	while (row < nb_rows)
	{
		col = 0;
		while (col < nb_cols)
		{
			points[row][col].position1.x = col - (double)(nb_cols - 1) / 2;
			points[row][col].position1.y = -row + (double)(nb_rows - 1) / 2;
			col++;
		}
		row++;
	}
}

void	find_position2(t_point **points, int nb_rows, int nb_cols, t_xyz pov)
{
	int row;
	int col;
	double k;

	row = 0;
	while (row < nb_rows)
	{
		col = 0;
		while (col < nb_cols)
		{
			k = 1 - (
			pov.x * points[row][col].position1.x +
			pov.y * points[row][col].position1.y +
			pov.z * points[row][col].position1.z) /
			(pow(pov.x, 2) + pow(pov.y, 2) + pow(pov.z, 2));
			
			points[row][col].position2.x =
			points[row][col].position1.x + k * pov.x;
			points[row][col].position2.y =
			points[row][col].position1.y + k * pov.y;
			points[row][col].position2.z =
			points[row][col].position1.z + k * pov.z;
			col++;
		}
		row++;
	}
}

t_xyz	find_u(t_xyz pov)
{
	t_xyz u;

	if (pov.x == 0 && pov.y == 0)
	{
		if (pov.z > 0)
			u = {1, 0, 0};
		else
			u = {-1, 0, 0};
		return (u);
	}
	u = {-pov.y, pov.x, 0};
	u = normalize(u);
	return (u);
}

t_xyz	find_v(t_xyz pov)
{
	t_xyz v;	
	t_xyz vector_pov_i;

	if (pov.x == 0 && pov.y == 0)
	{
		v = {0, 1, 0};
		return (v);
	}
	if (pov.z > -1 && pov.z < 1)
	{
		pov.z = 0;
		v = {0, 0, 1};
		return (v);
	}
	vector_pov_i = {-pov.x, -pov.y, (pow(pov.x, 2) + pow(pov.y, 2)) / pov.z};
	v = normalize(vector_pov_i);
	if (pov.z < 0)
	{
		v.x *= -1;
		v.y *= -1;
		v.z *= -1;
	}
	return (v);
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
