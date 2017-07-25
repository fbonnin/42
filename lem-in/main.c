/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:56:05 by fbonnin           #+#    #+#             */
/*   Updated: 2017/07/23 16:09:51 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_s s;

	s.moves = NULL;
	if (input(&s) == -1 || find_moves(&s) == -1)
		return (0);
	s.moves = list_moves_to_moves(&s.list_moves);
	sort_moves(s.moves, s.list_moves.nb_moves);
	print_lines(s.lines, s.nb_lines);
	print_moves(s.nodes, s.moves, s.list_moves.nb_moves);
	ft_printf("\n");
	free_all(&s.lines, &s.nodes, s.nb_nodes_expected, s.moves);
	return (0);
}

int		input(t_s *s)
{
	s->lines.first = NULL;
	s->lines.last = NULL;
	get_input(&s->lines, &s->nb_nodes_expected);
	s->nodes = alloc_nodes(s->nb_nodes_expected);
	parse_lines(s);
	if (s->nb_ants < 0 ||
	s->nodes[0].name == NULL || s->nodes[1].name == NULL)
	{
		ft_printf("ERROR\n");
		free_all(&s->lines, &s->nodes, s->nb_nodes_expected, s->moves);
		return (-1);
	}
	return (0);
}

int		find_moves(t_s *s)
{
	int i;

	s->list_moves.first = NULL;
	s->list_moves.last = NULL;
	s->list_moves.nb_moves = 0;
	i = 1;
	while (i <= s->nb_ants)
	{
		if (find_path(s->nodes, s->nb_nodes, &s->list_moves, i) == -1)
		{
			free_all(&s->lines, &s->nodes, s->nb_nodes_expected, s->moves);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	free_all(t_lines *lines, t_node **nodes, int nb_nodes_expected,
t_move *moves)
{
	free_lines(lines);
	free_nodes(nodes, nb_nodes_expected);
	free(moves);
}
