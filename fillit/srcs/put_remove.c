/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 19:03:56 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/24 22:22:40 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	put_remove(t_grid *grid, t_point *pos, t_tetri *t, int op)
{
	int	i;
	int c;

	c = (op == 0) ? t->letter : '.';
	i = 0;
	while (i < 4)
	{
		grid->cells[pos->y + t->points[i]->y][pos->x + t->points[i]->x] = c;
		i++;
	}
}
