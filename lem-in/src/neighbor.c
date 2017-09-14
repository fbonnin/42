/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:56:33 by fbonnin           #+#    #+#             */
/*   Updated: 2017/07/23 16:10:34 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_neighbor	*alloc_neighbor(void)
{
	t_neighbor *neighbor;

	neighbor = malloc(sizeof(t_neighbor));
	neighbor->next = NULL;
	return (neighbor);
}

void		add_neighbor(t_neighbor **neighbors, int i_neighbor)
{
	t_neighbor *neighbor;

	neighbor = alloc_neighbor();
	neighbor->i_node = i_neighbor;
	neighbor->next = *neighbors;
	*neighbors = neighbor;
}

void		free_neighbors(t_neighbor **neighbors)
{
	t_neighbor *neighbor;
	t_neighbor *next;

	neighbor = *neighbors;
	while (neighbor != NULL)
	{
		next = neighbor->next;
		free(neighbor);
		neighbor = next;
	}
	*neighbors = NULL;
}
