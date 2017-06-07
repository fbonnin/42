/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:32:24 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 16:32:26 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_list *list)
{
	t_list_elem *elem1;
	t_list_elem *elem2;

	if (list->size < 2)
		return ;
	elem1 = list->last->previous;
	elem2 = list->last;
	remove_last(list);
	remove_last(list);
	add_last(list, elem2);
	add_last(list, elem1);
}

void	push(t_list *list1, t_list *list2)
{
	t_list_elem *elem;

	if (list1->size == 0)
		return ;
	elem = list1->last;
	remove_last(list1);
	add_last(list2, elem);
}

void	rotate(t_list *list)
{
	t_list_elem *elem;

	if (list->size == 0)
		return ;
	elem = list->last;
	remove_last(list);
	add_first(list, elem);
}

void	reverse_rotate(t_list *list)
{
	t_list_elem *elem;

	if (list->size == 0)
		return ;
	elem = list->first;
	remove_first(list);
	add_last(list, elem);
}
