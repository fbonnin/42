#include "fdf.h"

void	put_pixel_to_image(void *image, int x, int y, int color)
{
	int *pixels;
	int bits_per_pixel;
	int size_line;
	int endian;

	pixels = (int *)mlx_get_data_addr(image, &bits_per_pixel, &size_line, &endian);
	pixels[y * size_line / 4 + x] = color;
}

int		expose(t_s *s)
{
	mlx_put_image_to_window(s->mlx, s->window, s->image, 0, 0);
	return (0);
}

int		end(int keycode, t_s *s)
{
	if (keycode == 53)
	{
		mlx_destroy_image(s->mlx, s->image);
		mlx_destroy_window(s->mlx, s->window);
		exit(0);
	}
	return (0);
}
