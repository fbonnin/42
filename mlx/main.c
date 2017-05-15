#include "stdlib.h"
#include "mlx.h"

typedef struct	s_s
{
	void	*mlx;
	void	*window;
	void	*image;
	int		width;
	int		height;
}				t_s;

void			put_pixel_to_image(t_s *s, int x, int y, int color)
{
	int *pixels;
	int bits_per_pixel;
	int size_line;
	int endian;

	pixels = (int *)mlx_get_data_addr(s->image, &bits_per_pixel, &size_line, &endian);
	pixels[y * s->width + x] = mlx_get_color_value(s->mlx, color);
}

int				end(int keycode, t_s *s)
{
	if (keycode == 53)
	{
		mlx_destroy_image(s->mlx, s->image);
		mlx_destroy_window(s->mlx, s->window);
		exit(0);
	}
	return (0);
}

int				main()
{
	t_s s;
	int x;
	int y;

	s.mlx = mlx_init();
	s.width = 300;
	s.height = 300;
	s.window = mlx_new_window(s.mlx, 400, 400, "test mlx");
	s.image = mlx_new_image(s.mlx, s.width, s.height);
	y = 0;
	while (y < s.height)
	{
		x = 0;
		while (x < s.width)
		{
			put_pixel_to_image(&s, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(s.mlx, s.window, s.image, 50, 50);
	mlx_key_hook(s.window, &end, &s);
	mlx_loop(s.mlx);
	return (0);
}
