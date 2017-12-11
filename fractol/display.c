void	generate_colors(t_s *s)
{
	int i;
	int c;
	int variation;

	i = 0;
	c = 0;
	while (i <= s->max_iterations_max)
	{
		s->colors[i] = rgb_to_int(c, c, c);
		if (c == 0)
			variation = 1;
		else if (c == 255)
			variation = -1;
		c += variation;
		i++;
	}
}

void	grid_to_image(t_s *s)
{
	int x;
	int y;

	x = 0;
	while (x < s->width)
	{
		y = 0;
		while (y < s->height)
		{
			put_pixel_to_image(s->image, x, y, s->colors[s->grid[y][x]]);
			y++;
		}
		x++;
	}
}

void	draw_fractal(t_s *s)
{
	fill_grid(s);
	grid_to_image(s);
	mlx_put_image_to_window(s->mlx, s->window, s->image, 0, 0);
}

void	init_display(t_s *s)
{
	s->pov = s->pov_init;
	s->cell_size = s->radius_init / (s->width / 2);
	s->max_iterations = s->max_iterations_init;
	s->point_julia = s->point_julia_init;
	s->julia_mode = 1;
	draw_fractal(s);
}
