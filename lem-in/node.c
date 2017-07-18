#include "lem-in.h"

void	alloc_nodes(t_node **nodes, int nb_nodes_expected)
{
	int i;

	*nodes = malloc(nb_nodes_expected * sizeof(t_node));
	i = 0;
	while (i < nb_nodes_expected)
	{
		(*nodes)[i].name = NULL;
		(*nodes)[i].neighbors = NULL;
		(*nodes)[i].time_available = 0;
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
