int	main(void)
{
	t_s s;

	s.mlx = mlx_init();
	s.width = 400;
	s.height = 400;
	s.window = mlx_new_window(s.mlx, s.width, s.height, "FDF");
	
}
