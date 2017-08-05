/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 20:52:30 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/24 20:52:56 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "stdlib.h"
#include "../libft/libft.h"

int	main(int ac, char **av)
{
	char	**tetris;
	int		count;
	t_grid	*grid;
	t_tetri **parsed;

	if (ac == 2)
		count = get_splited_file(av[1], &tetris);
	else
	{
		ft_putendl("usage: fillit source_file");
		return (0);
	}
	if (count <= 0)
	{
		ft_putendl("error");
		return (0);
	}
	parse_all_tetri(&parsed, tetris, count);
	create_grid(parsed, count, &grid);
	find_min_square(grid, parsed);
	print_grid(grid);
	return (0);
}
