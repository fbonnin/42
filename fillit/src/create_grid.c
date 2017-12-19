/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 12:49:53 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/24 22:08:30 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"
#include "libft/libft.h"

static int	get_min_square(int tetri_count)
{
	int	i;
	int square;

	i = 1;
	square = tetri_count * 2;
	while ((i * i) <= square && i < (square / 2))
		i++;
	return (i);
}

static int	set_rows(t_grid **grid, int grid_size)
{
	int i;

	i = 0;
	while (i < grid_size)
	{
		if (((*grid)->cells[i] = ft_strnew(grid_size)) == NULL)
		{
			while (--i >= 0)
				free((*grid)->cells[i]);
			free((*grid)->cells);
			free(*grid);
			return (-1);
		}
		i++;
	}
	return (0);
}

int			create_grid(t_tetri **tetris, int count, t_grid **grid)
{
	int		i;
	int		grid_size;

	i = -1;
	grid_size = 0;
	while (++i < count)
		grid_size += ft_max(tetris[i]->height, tetris[i]->width);
	if (((*grid) = (t_grid *)malloc(sizeof(t_grid))) == NULL)
		return (-1);
	if (((*grid)->cells = (char **)malloc(sizeof(char *) * grid_size)) == NULL)
	{
		free(*grid);
		return (-1);
	}
	if (set_rows(grid, grid_size) == -1)
		return (-1);
	(*grid)->max_size = grid_size;
	(*grid)->min_size = get_min_square(count);
	(*grid)->nb_tetris = count;
	clear_grid(grid);
	return (grid_size);
}
