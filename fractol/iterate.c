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
	while (z.x * z.x + z.y * z.y < 4 && nb_iterations <  s->max_iterations)
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
