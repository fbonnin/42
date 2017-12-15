/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:36 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:52:38 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "math.h"
# include "mlx.h"
# include "libft/libft.h"

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef enum	e_type
{
	mandelbrot,
	julia,
	burning_ship
}				t_type;

typedef struct	s_s
{
	void	*mlx;
	void	*window;
	void	*image;
	int		**grid;
	int		*colors;
	t_type	type;
	int		width;
	int		height;
	int		mouse_x;
	int		mouse_y;
	t_point	pov;
	t_point	pov_init;
	double	arrows_speed;
	double	cell_size;
	double	radius_init;
	double	zoom_speed;
	int		nb_zoom;
	int		nb_zoom_max;
	int		max_iterations;
	int		max_iterations_init;
	int		max_iterations_speed;
	int		max_iterations_max;
	t_point	point_julia;
	t_point	point_julia_init;
	int		julia_mode;
	int		color_set;
}				t_s;

int				rgb_to_int(int r, int g, int b);
void			put_pixel_to_image(void *image, int x, int y, int color);

int				usage(void);

void			init(t_s *s);
void			settings(t_s *s);
void			allocate(t_s *s);
void			end(t_s *s);

t_point			formula(t_point z, t_point c);
int				iterate(t_s *s, t_point point);
t_point			cell_to_point(t_s *s, int x, int y);
void			fill_grid(t_s *s);

void			grid_to_image(t_s *s);
void			draw_fractal(t_s *s);
void			init_display(t_s *s);

void			generate_colors(t_s *s);
void			generate_colors_2(t_s *s);
void			move_c(t_s *s, int i, int *c, int i_c);
int				random_bit(t_s *s, int i, int i_c);

void			manage_events(t_s *s);
int				expose_event(t_s *s);
int				mouse_event(int button, int x, int y, t_s *s);
int				mouse_move_event(int x, int y, t_s *s);

int				keyboard_event(int key, t_s *s);
void			arrow(int key, t_s *s);
void			change_max_iterations(int key, t_s *s);

void			zoom_in(t_s *s, t_point mouse);
void			zoom_out(t_s *s, t_point mouse);

#endif
