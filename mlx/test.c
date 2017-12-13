#include "mlx.h"
#include "stdlib.h"
#include "stdio.h"

int event_mouse(int button, int x, int y, void *p)
{
	printf("%d %d %d\n", button, x, y);
	return (0);
}

int event_key(int key, void *p)
{
	if (key == 53)
		exit(0);
	return (0);
}

int event_move(int x, int y, void *p)
{
	printf("%d %d\n", x, y);
	return (0);
}

int main()
{
	void *mlx;
	void *window;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 800, 800, "test");
	mlx_mouse_hook(window, event_mouse, NULL);
	mlx_hook(window, 6, 1 << 6, event_move, NULL);
	mlx_key_hook(window, event_key, NULL);
	mlx_loop(mlx);
}
