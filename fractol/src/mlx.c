#include "fractol.h"

int		rgb_to_int(int r, int g, int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

void	put_pixel_to_image(void *image, int x, int y, int color)
{
	int *pixels;
	int bits_per_pixel;
	int size_line;
	int endian;

	pixels = (int *)mlx_get_data_addr(image,
	&bits_per_pixel, &size_line, &endian);
	pixels[y * size_line / 4 + x] = color;
}
