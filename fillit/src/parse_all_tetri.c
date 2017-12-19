/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all_tetri.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 22:11:12 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 18:03:15 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"
#include "stdlib.h"

int	parse_all_tetri(t_tetri ***tetris, char **splited, int count)
{
	t_tetri	**parsed;
	int		i;

	i = 0;
	if ((parsed = malloc(sizeof(t_tetri *) * count)) == NULL)
		return (-1);
	while (i < count)
	{
		if (get_tetri(parsed + i, splited[i]) == -1)
		{
			free(*tetris);
			return (-1);
		}
		else
			scale_tetri(parsed[i]);
		parsed[i]->letter = 'A' + i;
		i++;
	}
	*tetris = parsed;
	return (i);
}
