/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:56:56 by fbonnin           #+#    #+#             */
/*   Updated: 2017/07/23 16:11:16 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_path(t_node *nodes, int nb_nodes,
t_list_moves *list_moves, int ant)
{
	int i_closest;

	initialize_bfs(nodes, nb_nodes);
	while (!nodes[1].reached)
	{
		i_closest = find_closest(nodes, nb_nodes);
		if (i_closest == -1)
		{
			ft_printf("ERROR\n");
			return (-1);
		}
		reach(nodes, i_closest);
	}
	save_moves(nodes, list_moves, ant);
	return (0);
}

void	initialize_bfs(t_node *nodes, int nb_nodes)
{
	int i;

	i = 0;
	while (i < nb_nodes)
	{
		nodes[i].reached = 0;
		nodes[i].time_reach = 2000000000;
		nodes[i].previous = -1;
		i++;
	}
	nodes[0].time_reach = 0;
}

int		find_closest(t_node *nodes, int nb_nodes)
{
	int min;
	int i_min;
	int i;

	min = 2000000000;
	i_min = -1;
	i = 0;
	while (i < nb_nodes)
	{
		if (!nodes[i].reached && nodes[i].time_reach < min)
		{
			min = nodes[i].time_reach;
			i_min = i;
		}
		i++;
	}
	return (i_min);
}

void	reach(t_node *nodes, int i_node)
{
	t_neighbor	*neighbor;
	int			time_reach;

	nodes[i_node].reached = 1;
	neighbor = nodes[i_node].neighbors;
	while (neighbor != NULL)
	{
		time_reach = ft_max(nodes[neighbor->i_node].time_available,
		nodes[i_node].time_reach + 1);
		if (time_reach < nodes[neighbor->i_node].time_reach)
		{
			nodes[neighbor->i_node].time_reach = time_reach;
			nodes[neighbor->i_node].previous = i_node;
		}
		neighbor = neighbor->next;
	}
}

void	save_moves(t_node *nodes, t_list_moves *list_moves, int ant)
{
	int		i_node;
	t_move	move;

	i_node = 1;
	while (i_node != 0)
	{
		move.ant = ant;
		move.destination = i_node;
		move.time = nodes[i_node].time_reach;
		add_list_move(list_moves, move);
		nodes[nodes[i_node].previous].time_available = nodes[i_node].time_reach;
		i_node = nodes[i_node].previous;
	}
}
