/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:40:07 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/18 16:40:34 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fcntl.h"
# include "math.h"
# include "mlx.h"
# include "libft/libft.h"

# define FDF_ERROR -1

typedef struct	s_xy_int
{
	int x;
	int y;
}				t_xy_int;

typedef struct	s_xy_double
{
	double x;
	double y;
}				t_xy_double;

typedef struct	s_xyz_double
{
	double x;
	double y;
	double z;
}				t_xyz_double;

typedef struct	s_point
{
	t_xyz_double	position1;
	t_xyz_double	position2;
	t_xy_double		position3;
	t_xy_int		position4;
}				t_point;

typedef struct	s_s
{
	t_xyz_double	pov;
	int				width;
	int				height;
	int				color;
	void			*mlx;
	void			*window;
	void			*image;
	char			*file_name;
	int				fd;
	int				nb_rows;
	int				nb_cols;
	t_point			**points;
	t_xyz_double	u;
	t_xyz_double	v;
	double			max_x3;
	double			max_y3;
}				t_s;

int				check_and_load_file(t_s *s);
int				check_file(t_s *s);
int				check_file2(t_s *s);
int				find_nb_cols(char **split_line);
void			free_split_line(char **split_line);
int				alloc_points(t_s *s);
void			free_points(t_s *s);
int				load_file(t_s *s);
void			convert_line(t_s *s, int row, char **split_line);
int				error_file(t_s *s);

t_xyz_double	normalize(t_xyz_double vector);

void			make_calculations(t_s *s);
void			find_position1(t_s *s);
t_xyz_double	find_projection(t_s *s, t_xyz_double position);
void			find_position2(t_s *s);
void			find_u(t_s *s);
void			find_v(t_s *s);
void			find_position3(t_s *s);
void			find_position3_2(t_s *s);
void			find_max_position3(t_s *s);
void			find_position4(t_s *s);

void			draw_result(t_s *s);
void			draw_segments(t_s *s);
void			draw_segment(t_s *s, t_xy_int p1, t_xy_int p2);
void			draw_segment_horizontal(t_s *s,
					t_xy_double pixel1, t_xy_double pixel2);
void			draw_segment_vertical(t_s *s,
					t_xy_double pixel1, t_xy_double pixel2);

void			put_pixel_to_image(void *image, int x, int y, int color);
int				expose(t_s *s);
int				key(int keycode, t_s *s);

#endif
