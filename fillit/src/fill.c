/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 15:52:12 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 12:24:13 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		fill(t_grid *grid, t_tetri **tetris, int i_tetri)
{
	t_tetri *tetri;
	t_point pos;

	if (i_tetri == grid->nb_tetris)
		return (1);
	tetri = tetris[i_tetri];
	pos.y = 0;
	while (pos.y < grid->min_size - (tetri->height - 1))
	{
		pos.x = 0;
		while (pos.x < grid->min_size - (tetri->width - 1))
		{
			if (can_put(grid, &pos, tetri))
			{
				put_remove(grid, &pos, tetri, 0);
				if (fill(grid, tetris, i_tetri + 1))
					return (1);
				put_remove(grid, &pos, tetri, 1);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (0);
}
