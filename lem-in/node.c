#include "lem-in.h"

t_node	*alloc_nodes(int nb_nodes_expected)
{
	t_node *nodes;
	int		i;

	nodes = malloc(nb_nodes_expected * sizeof(t_node));
	i = 0;
	while (i < nb_nodes_expected)
	{
		nodes[i].name = NULL;
		nodes[i].neighbors = NULL;
		nodes[i].time_available = 0;
		i++;
	}
}

void	free_nodes(t_node **nodes, int nb_nodes_expected)
{
	int i;

	i = 0;
	while (i < nb_nodes_expected)
	{
		free((*nodes)[i].name);
		free_neighbors(&(*nodes)[i].neighbors);
		i++;
	}
	free(*nodes);
	*nodes = NULL;
}

int		name_to_index(t_node *nodes, int nb_nodes, char *name)
{
	int result;
	int i;

	result = -1;
	i = 0;
	while (i < nb_nodes)
	{
		if (ft_strequ(nodes[i].name, name) == 1)
		{
			result = i;
			break;
		}
		i++;
	}
	return (result);
}
