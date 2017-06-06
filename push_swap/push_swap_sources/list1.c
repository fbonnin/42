#include "push_swap.h"

void		initialize_list(t_list *list)
{
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

t_list_elem	*create_list_elem(int number)
{
	t_list_elem *elem;

	elem = malloc(sizeof(t_list_elem));
	if (elem == NULL)
		return (NULL);
	elem->number = number;
	return (elem);
}

void		free_list(t_list *list)
{
	t_list_elem *elem;

	elem = list->first;
	while (elem != NULL)
	{
		free(elem);
		elem = elem->next;
	}
}
