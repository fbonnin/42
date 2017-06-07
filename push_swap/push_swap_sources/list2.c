/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:24:42 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 17:01:03 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_first(t_list *list, t_list_elem *elem)
{
	if (elem == NULL)
		return ;
	elem->previous = NULL;
	elem->next = list->first;
	if (list->size == 0)
		list->last = elem;
	else
		list->first->previous = elem;
	list->first = elem;
	list->size++;
}

void	add_last(t_list *list, t_list_elem *elem)
{
	if (elem == NULL)
		return ;
	elem->previous = list->last;
	elem->next = NULL;
	if (list->size == 0)
		list->first = elem;
	else
		list->last->next = elem;
	list->last = elem;
	list->size++;
}

void	remove_first(t_list *list)
{
	if (list->size == 0)
		return ;
	if (list->size == 1)
	{
		list->first = NULL;
		list->last = NULL;
	}
	else
	{
		list->first = list->first->next;
		list->first->previous = NULL;
	}
	list->size--;
}

void	remove_last(t_list *list)
{
	if (list->size == 0)
		return ;
	if (list->size == 1)
	{
		list->first = NULL;
		list->last = NULL;
	}
	else
	{
		list->last = list->last->previous;
		list->last->next = NULL;
	}
	list->size--;
}
