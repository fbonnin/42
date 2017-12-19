/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:09:22 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 17:10:13 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	numbers_to_a(int *numbers, int nb_numbers, t_list *a)
{
	int			i;
	t_list_elem	*elem;

	i = 0;
	while (i < nb_numbers)
	{
		elem = create_list_elem(numbers[i++]);
		if (elem == NULL)
			return (CHECK_ERROR);
		add_first(a, elem);
	}
	return (0);
}

int	do_operations(t_list *a, t_list *b, char *line)
{
	if (ft_strequ(line, "sa"))
		swap(a);
	else if (ft_strequ(line, "sb"))
		swap(b);
	else if (ft_strequ(line, "ss"))
	{
		swap(a);
		swap(b);
	}
	else if (ft_strequ(line, "pa"))
		push(b, a);
	else if (ft_strequ(line, "pb"))
		push(a, b);
	else
		return (do_operations_2(a, b, line));
	return (0);
}

int	do_operations_2(t_list *a, t_list *b, char *line)
{
	if (ft_strequ(line, "ra"))
		rotate(a);
	else if (ft_strequ(line, "rb"))
		rotate(b);
	else if (ft_strequ(line, "rr"))
	{
		rotate(a);
		rotate(b);
	}
	else if (ft_strequ(line, "rra"))
		reverse_rotate(a);
	else if (ft_strequ(line, "rrb"))
		reverse_rotate(b);
	else if (ft_strequ(line, "rrr"))
	{
		reverse_rotate(a);
		reverse_rotate(b);
	}
	else
		return (CHECK_ERROR);
	return (0);
}

int	check_result(t_list *a, t_list *b)
{
	t_list_elem *elem;

	if (b->size != 0)
		return (0);
	if (a->size == 0)
		return (1);
	elem = a->first;
	while (elem->next != NULL)
	{
		if (elem->number < elem->next->number)
			return (0);
		elem = elem->next;
	}
	return (1);
}
