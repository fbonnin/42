/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:52:47 by fbonnin           #+#    #+#             */
/*   Updated: 2017/12/15 18:52:50 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_s *s)
{
	settings(s);
	allocate(s);
	generate_colors(s);
	init_display(s);
}

void	settings(t_s *s)
{
	s->window = NULL;
	s->image = NULL;
	s->grid = NULL;
	s->colors = NULL;
	s->mouse_x = s->width / 2;
	s->mouse_y = s->height / 2;
	s->pov_init.x = 0;
	s->pov_init.y = 0;
	s->arrows_speed = 0.1;
	s->radius_init = 2;
	s->zoom_speed = 0.9;
	s->nb_zoom = 0;
	s->nb_zoom_max = 1;
	s->max_iterations_init = 50;
	s->max_iterations_speed = 10;
	s->max_iterations_max = 1000;
	s->point_julia_init.x = 0;
	s->point_julia_init.y = 0;
	s->color_set = 0;
}

void	allocate(t_s *s)
{
	int i;

	if ((s->mlx = mlx_init()) == NULL)
		end(s);
	if ((s->window = mlx_new_window(s->mlx, s->width, s->height, "Fractol")) ==
	NULL)
		end(s);
	if ((s->image = mlx_new_image(s->mlx, s->width, s->height)) == NULL)
		end(s);
	if ((s->grid = malloc(sizeof(int *) * s->height)) == NULL)
		end(s);
	i = 0;
	while (i < s->height)
		s->grid[i++] = NULL;
	i = 0;
	while (i < s->height)
		if ((s->grid[i++] = malloc(sizeof(int) * s->width)) == NULL)
			end(s);
	if ((s->colors = malloc(sizeof(int) * (s->max_iterations_max + 1))) == NULL)
		end(s);
}

void	end(t_s *s)
{
	int i;

	if (s->window != NULL)
		mlx_destroy_window(s->mlx, s->window);
	if (s->image != NULL)
		mlx_destroy_image(s->mlx, s->image);
	if (s->grid != NULL)
	{
		i = 0;
		while (i < s->height)
			free(s->grid[i++]);
	}
	free(s->grid);
	free(s->colors);
	exit(0);
}
