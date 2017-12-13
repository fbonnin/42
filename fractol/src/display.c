#include "fractol.h"

void	generate_colors(t_s *s)
{
	int i;
	int r;
	int g;
	int b;
	int pas;

	i = 0;
	r = 128;
	g = 128;
	b = 128;
	pas = 7;
	while (i <= s->max_iterations_max)
	{
		s->colors[i] = rgb_to_int(r, g, b);
		if (r < 255 && (int)(cos(i * 3) * 1000 * pow(10, s->color_set)) % 2 == 0)
			r += pas;
		else if (r > 0)
			r -= pas;
		if (g < 255 && (int)(cos(i * 3 + 1) * 1000 * pow(10, s->color_set)) % 2 == 0)
			g += pas;
		else if (g > 0)
			g -= pas;
		if (b < 255 && (int)(cos(i * 3 + 2) * 1000 * pow(10, s->color_set)) % 2 == 0)
			b += pas;
		else if (b > 0)
			b -= pas;
		i++;
	}
	s->color_set = (s->color_set + 1) % 7;
}

/*void	generate_colors(t_s *s)
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
}*/

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
	s->cell_size = s->radius_init / (ft_min(s->width, s->height) / 2);
	s->max_iterations = s->max_iterations_init;
	s->point_julia = s->point_julia_init;
	s->julia_mode = 1;
	draw_fractal(s);
}
