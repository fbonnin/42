#include "lem-in.h"

t_list_move *alloc_list_move()
{
	t_list_move *list_move;

	list_move = malloc(sizeof(t_list_move));
	list_move->next = NULL;
	return (list_move);
}

void		add_list_move(t_list_moves *list_moves, t_move move)
{
	t_list_move *list_move;

	list_move = alloc_list_move();
	list_move->move = move;
	if (list_moves->first == NULL)
		list_moves->first = list_move;
	else
		list_moves->last->next = list_move;
	list_moves->last = list_move;
	list_moves->nb_moves++;
}

void		free_list_moves(t_list_moves *list_moves)
{
	t_list_move *list_move;
	t_list_move *next;

	list_move = list_moves->first;
	while (list_move != NULL)
	{
		next = list_move->next;
		free(list_move);
		list_move = next;
	}
	list_moves->first = NULL;
	list_moves->last = NULL;
}
