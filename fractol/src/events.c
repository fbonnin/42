#include "fractol.h"

void	manage_events(t_s *s)
{
	mlx_expose_hook(s->window, expose_event, s);
	mlx_key_hook(s->window, keyboard_event, s);
	mlx_mouse_hook(s->window, mouse_event, s);
	mlx_hook(s->window, MotionNotify, PointerMotionMask, mouse_move_event, s);
	mlx_loop(s->mlx);
}

int		expose_event(t_s *s)
{
	mlx_put_image_to_window(s->mlx, s->window, s->image, 0, 0);
	return (0);
}

int		mouse_event(int button, int x, int y, t_s *s)
{
	t_point mouse;

	mouse = cell_to_point(s, x, y);
	if (button == /*up*/)
		zoom_in(s, mouse);
	else if (button == /*down*/)
		zoom_out(s, mouse);
	return (0);
}

int		mouse_move_event(int x, int y, t_s *s)
{
	s->mouse_x = x;
	s->mouse_y = y;
	if (s->type == julia && s->julia_mode)
	{
		s->point_julia = cell_to_point(s, x, y);
		draw_fractal(s);
	}
}
