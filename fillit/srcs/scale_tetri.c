/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_tetri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:51:21 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/24 22:07:15 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

static void	apply_scale(t_tetri *tetri, t_point *max, t_point *min)
{
	int	i;

	i = 0;
	while (i < tetri->points_count)
	{
		tetri->points[i]->x -= min->x;
		tetri->points[i]->y -= min->y;
		i++;
	}
	tetri->width = (max->x - min->x) + 1;
	tetri->height = (max->y - min->y) + 1;
}

static void	init_points(t_point *min, t_point *max, t_tetri *tetri)
{
	min->x = tetri->points[0]->x;
	min->y = tetri->points[0]->y;
	max->x = tetri->points[1]->x;
	max->y = tetri->points[1]->y;
}

int			scale_tetri(t_tetri *tetri)
{
	t_point	*min;
	t_point	*max;
	int		i;

	if ((min = (t_point *)malloc(sizeof(t_point))) == NULL)
		return (-1);
	if ((max = (t_point *)malloc(sizeof(t_point))) == NULL)
		return (-1);
	i = -1;
	init_points(min, max, tetri);
	while (++i < tetri->points_count)
	{
		if (tetri->points[i]->x < min->x)
			min->x = tetri->points[i]->x;
		if (tetri->points[i]->y < min->y)
			min->y = tetri->points[i]->y;
		if (tetri->points[i]->x > max->x)
			max->x = tetri->points[i]->x;
		if (tetri->points[i]->y > max->y)
			max->y = tetri->points[i]->y;
	}
	apply_scale(tetri, max, min);
	free(min);
	free(max);
	return (1);
}
