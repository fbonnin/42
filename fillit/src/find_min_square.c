/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_min_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:17:38 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 18:13:15 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		find_min_square(t_grid *grid, t_tetri **tetris)
{
	while (!fill(grid, tetris, 0))
	{
		grid->min_size++;
		clear_grid(&grid);
	}
	return (1);
}
