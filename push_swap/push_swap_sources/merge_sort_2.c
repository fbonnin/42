/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:28:53 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/09 15:28:55 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

void	push_left(t_push_swap *s, int save, t_merge_sort *v)
{
	if (v->i_list == 0)
	{
		if (v->a.last->number < v->b.last->number)
		{
			v->i_a++;
			v->i_sub_a++;
		}
		else
		{
			push(&v->b, &v->a);
			do_operation(s, save, pa);
			v->i_b++;
			v->i_sub_b++;
		}
		rotate(&v->a);
		do_operation(s, save, ra);
	}
}

void	push_right(t_push_swap *s, int save, t_merge_sort *v)
{
	if (v->i_list == 1)
	{
		if (v->a.last->number < v->b.last->number)
		{
			push(&v->a, &v->b);
			do_operation(s, save, pb);
			v->i_a++;
			v->i_sub_a++;
		}
		else
		{
			v->i_b++;
			v->i_sub_b++;
		}
		rotate(&v->b);
		do_operation(s, save, rb);
	}
}

void	empty_a(t_push_swap *s, int save, t_merge_sort *v)
{
	while (v->i_a < v->size_a && v->i_sub_a < v->size_sub)
	{
		if (v->i_list == 0)
		{
			rotate(&v->a);
			do_operation(s, save, ra);
		}
		else
		{
			push(&v->a, &v->b);
			do_operation(s, save, pb);
			rotate(&v->b);
			do_operation(s, save, rb);
		}
		v->i_a++;
		v->i_sub_a++;
	}
}

void	empty_b(t_push_swap *s, int save, t_merge_sort *v)
{
	while (v->i_b < v->size_b && v->i_sub_b < v->size_sub)
	{
		if (v->i_list == 0)
		{
			push(&v->b, &v->a);
			do_operation(s, save, pa);
			rotate(&v->a);
			do_operation(s, save, ra);
		}
		else
		{
			rotate(&v->b);
			do_operation(s, save, rb);
		}
		v->i_b++;
		v->i_sub_b++;
	}
}
