#include "fdf.h"

int		alloc_points(t_s *s)
{
	int row;

	if ((s->points = malloc(s->nb_rows * sizeof(t_point *))) == NULL)
		return (FDF_ERROR);
	row = 0;
	while (row < s->nb_rows)
	{
		if ((s->points[row] = malloc(s->nb_cols * sizeof(t_point))) == NULL)
		{
			row--;
			while (row >= 0)
			{
				free(s->points[row]);
				row--;
			}
			free(s->points);
			return (FDF_ERROR);
		}
		row++;
	}
	return (0);
}

void	free_points(t_s *s)
{
	int row;

	row = 0;
	while (row < s->nb_rows)
	{
		free(s->points[row]);
		row++;
	}
	free(s->points);
}

int	load_file(t_s *s)
{
	int		row;
	int		col;
	char	*line;
	char	**split_line;

	if ((s->fd = open(s->file_name, O_RDONLY)) == -1)
		return (FDF_ERROR);
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
	if (check_file(s) == FDF_ERROR)
		return (FDF_ERROR);
	if (alloc_points(s) == FDF_ERROR)
		return (FDF_ERROR);
	if (load_file(s) == FDF_ERROR)
	{
		free_points(s);
		return (FDF_ERROR);
	}
	return (0);
}
