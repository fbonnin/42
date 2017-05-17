#include "fdf.h"

void	initialize_s(t_s *s)
{
	s->pov.x = 0;
	s->pov.y = 0;
	s->pov.z = 0;
	s->width = 400;
	s->height = 400;
	s->color = 0x00FFFFFF
	s->mlx = NULL;
	s->window = NULL;
	s->image = NULL;
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

int	main(int ac, char **av)
{
	t_s s;

	initialize_s(&s);
	if (s.pov.x == 0 && s.pov.y == 0 && s.pov.z == 0)
		return (error(&s));
	if (ac != 2)
		return (error(&s));
	s.file_name = ft_strdup(av[1]);
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
