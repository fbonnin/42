#include "lem-in.h"

int		main(void)
{
	t_s s;

	s.moves = NULL;
	if (input(&s) == -1 || find_moves(&s) == -1)
		return (0);
}

int		input(t_s *s)
{
	s->lines->first = NULL;
	s->lines->last = NULL;
	get_input(&s->lines, &s->nb_nodes_expected);
	s->nodes = alloc_nodes(s->nb_nodes_expected);
	parse_lines(s);
	if (s->nb_ants < 0 ||
	s->nb_nodes[0].name == NULL || s->nb_nodes[1].name == NULL)
	{
		ft_printf("ERROR\n");
		free_all(&s->lines, &s->nodes, s->nb_nodes, s->moves);
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
