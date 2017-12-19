/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_is_valide.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:50:45 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 18:22:17 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	tetri_is_valide(char *buff)
{
	int		i;
	int		j;
	char	*buffer;

	buffer = buff;
	i = 0;
	if (ft_strlen(buff) < 19)
		return (0);
	while (i++ < 4)
	{
		j = 4;
		while (j--)
		{
			if (!(*buffer == '.' || *buffer == '#'))
				return (0);
			else
				buffer++;
		}
		buffer++;
	}
	return ((*buffer == '\0' || *buffer == '\n'));
}
