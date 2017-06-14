/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 15:41:07 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/14 15:41:33 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	r_to_min(t_list *a)
{
	int			min_number;
	t_list_elem	*elem;
	int			result;

	min_number = list_min(a);
	elem = a->last;
	result = 0;
	while (elem->number != min_number)
	{
		elem = elem->previous;
		result++;
	}
	return (result);
}

static int	rr_to_min(t_list *a)
{
	int			min_number;
	t_list_elem	*elem;
	int			result;

	min_number = list_min(a);
	elem = a->first;
	result = 1;
	while (elem->number != min_number)
	{
		elem = elem->next;
		result++;
	}
	return (result);
}

static void	rotate_to_min(t_push_swap *s, int save, t_list *a)
{
	int r;
	int rr;

	r = r_to_min(a);
	rr = rr_to_min(a);
	if (r < rr)
	{
		while (r-- > 0)
		{
			rotate(a);
			do_operation(s, save, ra);
		}
	}
	else
	{
		while (rr-- > 0)
		{
			reverse_rotate(a);
			do_operation(s, save, rra);
		}
	}
}

static void	sort(t_push_swap *s, int save, t_list *a, t_list *b)
{
	rotate_to_min(s, save, a);
	while (!list_sorted(a))
	{
		push(a, b);
		do_operation(s, save, pb);
		rotate_to_min(s, save, a);
	}
	while (b->size != 0)
	{
		push(b, a);
		do_operation(s, save, pa);
	}
}

int			selection_sort(t_push_swap *s, int save)
{
	t_list		a;
	t_list		b;
	int			i;
	t_list_elem	*elem;

	initialize_list(&a);
	initialize_list(&b);
	i = 0;
	while (i < s->nb_numbers)
	{
		if ((elem = create_list_elem(s->numbers[i++])) == NULL)
		{
			free_list(&a);
			return (PS_ERROR);
		}
		add_first(&a, elem);
	}
	sort(s, save, &a, &b);
	free_list(&a);
	free_list(&b);
	return (s->nb_operations);
}
