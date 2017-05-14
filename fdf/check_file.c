int			file_error(t_s *s)
{
	close(s->fd);
	return (ERROR);
}

int			find_nb_cols(char **split_line)
{
	int nb_cols;

	nb_cols = 0;
	while (split_line[nb_cols] != NULL)
		nb_cols++;
	return (nb_cols);
}

void		free_split_line(char **split_line)
{
	int col;

	col = 0;
	while (split_line[col] != NULL)
	{
		free(split_line[col]);
		col++;
	}
	free(split_line);
}

int    		check_file(t_s *s, char *file_name)
{
	int		fd;
    char	*line;
    char	**split_line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (ERROR);
	if (ft_get_next_line(fd, &line) <= 0)
		return (file_error(s));
	split_line = ft_strsplit(line, ' ');
	free(line);
	if (split_line == NULL)
		return (file_error(s));
	s->nb_cols = find_nb_cols(split_line);
	free_split_line(split_line);
	if (s->nb_cols == 0)
		return (file_error(s));
	s->nb_rows = 1;
	return (check_file2(s, fd));
}

static int	check_file2(t_s *s, int fd)
{
	char	*line;
	int		r;
	char	**split_line;
	int		nb_cols;

	while ((r = ft_get_next_line(fd, &line)) > 0)
	{
		split_line = ft_strsplit(line, ' ');
		free(line);
		if (split_line == NULL)
			return (file_error(s));
		nb_cols = find_nb_cols(split_line);
		free_split_line(split_line);
		if (nb_cols != s->nb_cols)
			return (file_error(s));
		s->nb_cols = nb_cols;
		s->nb_rows++;
	}
	close(s->fd);
	if (r == -1)
		return (ERROR);
	return (0);
}
