/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_match_rules.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:55:05 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 18:24:53 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"

int	tetri_match_rules(char *buffer)
{
	int		i;
	int		neigbors;
	int		pc;

	pc = 0;
	i = 0;
	neigbors = 0;
	while (i < 19 && buffer[i])
	{
		if (buffer[i] == '#')
		{
			pc++;
			if (i >= 5 && buffer[i - 5] == '#')
				neigbors++;
			if (i <= 14 && buffer[i + 5] == '#')
				neigbors++;
			if (i <= 18 && buffer[i + 1] == '#')
				neigbors++;
			if (i >= 1 && buffer[i - 1] == '#')
				neigbors++;
		}
		i++;
	}
	return (neigbors >= 6 && neigbors <= 8 && pc == 4);
}
