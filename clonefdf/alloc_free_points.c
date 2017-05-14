int		alloc_points(t_s *s)
{
	int row;

	if ((s->points = malloc(s->nb_rows * sizeof(t_point *))) == NULL)
		return (ERROR);
	row = 0;
	while (row < s->nb_rows)
	{
		if ((s->points[row] = malloc(s->nb_cols * sizeof(t_point))) == NULL)
		{
			row--;
			while (row >= 0)
			{
				free(s->points[row]);
				row--;
			}
			free(s->points);
			return (ERROR);
		}
		row++;
	}
	return (0);
}

void	free_points(t_s *s)
{
	int row;

	row = 0;
	while (row < s->nb_rows)
	{
		free(s->points[row]);
		row++;
	}
	free(s->points);
}
