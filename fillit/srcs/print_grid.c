/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:10:33 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/24 22:08:42 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fillit.h"

void	print_grid(t_grid *grid)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->min_size)
	{
		x = 0;
		while (x < grid->min_size)
		{
			ft_putchar(grid->cells[y][x++]);
		}
		ft_putchar('\n');
		y++;
	}
}
