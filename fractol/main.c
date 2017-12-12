int	main(int ac, char **av)
{
	t_s s;

	if (ac != 4)
		return (usage());
	if (ft_strequ(av[1], "m"))
		s.type = mandelbrot;
	else if (ft_strequ(av[1], "j"))
		s.type = julia;
	else if (ft_strequ(av[1], "b"))
		s.type = burning_ship;
	else
		return (usage());
	s.width = ft_atoi(av[2]);
	s.height = ft_atoi(av[3]);
	if (s.width < 1 || s.height < 1)
		return (usage());
	if (s.width % 2 == 0)
		s.width++;
	if (s.height % 2 == 0)
		s.height++;
	init(&s);
	manage_events(&s);
	return (0);
}

int	usage(void)
{
	ft_printf(1, "usage: ./fractol fractal_name window_width window_height\n");
	ft_printf(1, "Available fractals :\n");
	ft_printf(1, "m (mandelbrot)\n");
	ft_printf(1, "j (julia)\n");
	ft_printf(1, "b (burning ship)\n");
	return (0);
}
