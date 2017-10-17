/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:35:51 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/19 15:17:56 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialize_s(t_s *s)
{
	s->color = 0x00FFFFFF;
	s->mlx = NULL;
	s->window = NULL;
	s->image = NULL;
}

void	set_parameters(char **av, t_s *s)
{
	s->file_name = ft_strdup(av[1]);
	s->pov.x = ft_atoi(av[2]);
	s->pov.y = ft_atoi(av[3]);
	s->pov.z = ft_atoi(av[4]);
	s->width = ft_atoi(av[5]);
	s->height = ft_atoi(av[6]);
}

int		usage(void)
{
	ft_putstr("usage : ./fdf file_name pov.x pov.y pov.z ");
	ft_putendl("window_width window_height");
	return (0);
}

int		error(t_s *s)
{
	if (s->image != NULL)
		mlx_destroy_image(s->mlx, s->image);
	if (s->window != NULL)
		mlx_destroy_window(s->mlx, s->window);
	ft_putendl("error");
	return (0);
}

int		main(int ac, char **av)
{
	t_s s;

	initialize_s(&s);
	if (ac != 7)
		return (usage());
	set_parameters(av, &s);
	if (s.pov.x == 0 && s.pov.y == 0 && s.pov.z == 0)
		return (error(&s));
	if (s.width < 1 || s.height < 1)
		return (error(&s));
	if (check_and_load_file(&s) == FDF_ERROR)
		return (error(&s));
	if ((s.mlx = mlx_init()) == NULL)
		return (error(&s));
	if ((s.window = mlx_new_window(s.mlx, s.width, s.height, "FDF")) == NULL)
		return (error(&s));
	if ((s.image = mlx_new_image(s.mlx, s.width, s.height)) == NULL)
		return (error(&s));
	make_calculations(&s);
	draw_result(&s);
	mlx_expose_hook(s.window, &expose, &s);
	mlx_key_hook(s.window, &key, &s);
	mlx_loop(s.mlx);
	return (0);
}
