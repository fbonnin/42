#include "lem-in.h"

void	parse_lines(t_params_parsing *p)
{
	t_line	*line;
	int		stop;
	int		part;
	int		cmd;

	p->nb_lines = 0;
	p->nb_nodes = 2;
	line = p->lines.first;
	stop = 0;
	part = 0;
	cmd = 0;
	while (line != NULL && !stop)
	{
		if (!parse_sharp(p->nodes, line->str, &stop, &cmd))
			if (!parse_part0(&p->nb_ants, line->str, &stop, &part))
				if (p->nb_lines > p->nb_nodes_expected ||
				!parse_part1(p->nodes, &p->nb_nodes, line->str, &cmd))
					parse_part2(p->nodes, p->nb_nodes, line->str, &stop);
		if (!stop)
			p->nb_lines++;
		line = line->next;
	}
}

int		parse_sharp(t_node *nodes, char *str, int *stop, int *cmd)
{
	if (str[0] != '#')
		return (0);
	else if (ft_strequ(str, "##start") == 1)
	{
		*cmd = 1;
		if (nodes[0].name != NULL)
			*stop = 1;
	}
	else if (ft_strequ(str, "##end") == 1)
	{
		*cmd = 2;
		if (nodes[1].name != NULL)
			*stop = 1;
	}
	return (1);
}

int		parse_part0(int *nb_ants, char *str, int *stop, int *part)
{
	if (part != 0)
		return (0);
	*nb_ants = ft_atoi(str);
	if (*nb_ants < 0)
		*stop = 1;
	*part = 1;
	return (1);
}

int		parse_part1(t_node *nodes, int *nb_nodes, char *str, int *cmd)
{
	char	**words;
	int		i_node;

	words = ft_strsplit(str, ' ');
	i_node = name_to_index(nodes, nb_nodes, words[0]);
	if (i_node == -1)
	{
		if (*cmd == 1)
			nodes[0].name = ft_strdup(words[0]);
		else if (*cmd == 2)
			nodes[1].name = ft_strdup(words[0]);
		else
			nodes[(*nb_nodes)++].name = ft_strdup(words[0]);
	}
	free_words(words);
	*cmd = 0;
	return (1);
}

void	parse_part2(t_node *nodes, int nb_nodes, char *str, int *stop)
{
	char	**words;
	int		i_node1;
	int		i_node2;

	words = ft_strsplit(str, '-');
	i_node1 = name_to_index(nodes, nb_nodes, words[0]);
	i_node2 = name_to_index(nodes, nb_nodes, words[1]);
	if (i_node1 == -1 || i_node2 == -1)
		*stop = 1;
	else
	{
		add_neighbor(&nodes[i_node1].neighbors, i_node2);
		add_neighbor(&nodes[i_node2].neighbors, i_node1);
	}
}
