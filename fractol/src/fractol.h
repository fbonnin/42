#ifndef FRACTOL_H
# define FRACTOL_H

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct	e_type
{
	mandelbrot,
	julia,
	burning_ship
}				t_type;

int				usage(void);

void			init(t_s *s);
void			settings(t_s *s);
void			allocate(t_s *s);
void			end(t_s *s);

t_point			formula(t_point z, t_point c);
int				iterate(t_s *s, t_point point);
t_point			cell_to_point(t_s *s, int x, int y);
void			fill_grid(t_s *s);

void			generate_colors(t_s *s);
void			grid_to_image(t_s *s);
void			draw_fractal(t_s *s);
void			init_display(t_s *s);

void			manage_events(t_s *s);
int				expose_event(t_s *s);
int				mouse_move_event(int x, int y, t_s *s);

int				keyboard_event(int key, t_s *s);
void			arrow(int key, t_s *s);
void			change_max_iterations(int key, t_s *s);

void			zoom_in(t_s *s, t_point mouse);
void			zoom_out(t_s *s, t_point mouse);

#endif
