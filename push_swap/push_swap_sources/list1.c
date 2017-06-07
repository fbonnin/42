/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:20:33 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 17:00:51 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
