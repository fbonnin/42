#include "stdlib.h"
#include "mlx.h"

typedef struct	s_s
{
	void *mlx;
	void *window;
}				t_s;

int				end(int keycode, t_s *s)
{
	if (keycode == 53)
	{
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
	s.window = mlx_new_window(s.mlx, 400, 400, "test mlx");
	y = 100;
	while (y < 300)
	{
		x = 100;
		while (x < 300)
		{
			mlx_pixel_put(s.mlx, s.window, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_key_hook(s.window, &end, &s);
	mlx_loop(s.mlx);
	return (0);
}
