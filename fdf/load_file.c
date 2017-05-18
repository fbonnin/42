/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:34:14 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/18 16:37:39 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		load_file(t_s *s)
{
	int		row;
	char	*line;
	char	**split_line;

	if ((s->fd = open(s->file_name, O_RDONLY)) == -1)
		return (FDF_ERROR);
	row = 0;
	while (row < s->nb_rows)
	{
		if (ft_get_next_line(s->fd, &line) <= 0)
			return (error_file(s));
		split_line = ft_strsplit(line, ' ');
		free(line);
		if (split_line == NULL)
			return (error_file(s));
		convert_line(s, row, split_line);
		free_split_line(split_line);
		row++;
	}
	close(s->fd);
	return (0);
}

void	convert_line(t_s *s, int row, char **split_line)
{
	int col;

	col = 0;
	while (col < s->nb_cols)
	{
		s->points[row][col].position1.z = ft_atoi(split_line[col]);
		col++;
	}
}

int		error_file(t_s *s)
{
	close(s->fd);
	return (FDF_ERROR);
}
