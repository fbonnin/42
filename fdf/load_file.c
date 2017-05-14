int	load_file(t_s *s)
{
	int		row;
	int		col;
	char	*line;
	char	**split_line;

	if ((s->fd = open(s->file_name, O_RDONLY)) == -1)
		return (ERROR);
	row = 0;
	while (row < s->nb_rows)
	{
		if (ft_get_next_line(s->fd, &line) == -1)
			return (file_error(s));
		if ((split_line = ft_strsplit(line, ' ')) == NULL)
			return (file_error(s));
		free(line);
		col = 0;
		while (col < s->nb_cols)
		{
			points[row][col].z = ft_atoi(split_line[col]);
			col++;
		}
		free_split_line(split_line);
		row++;
	}
	close(s->fd);
	return (0);
}

int	check_and_load_file(t_s *s)
{
	if (check_file(s) == ERROR)
		return (ERROR);
	if (alloc_points(s) == ERROR)
		return (ERROR);
	if (load_file(s) == ERROR)
	{
		free_points(s);
		return (ERROR);
	}
	return (0);
}
