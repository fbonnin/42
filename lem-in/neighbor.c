#include "lem-in.h"

t_neighbor *alloc_neighbor()
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
