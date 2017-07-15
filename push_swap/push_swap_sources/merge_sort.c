/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:27:39 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/09 15:28:42 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

int		merge_sort(t_push_swap *s, int save)
{
	t_merge_sort v;

	initialize(s, save, &v);
	while (v.size_sub < s->nb_numbers)
	{
		set_indexes(&v);
		while (v.i_a < v.size_a)
		{
			v.i_sub_a = 0;
			v.i_sub_b = 0;
			while (v.i_a < v.size_a && v.i_sub_a < v.size_sub &&
			v.i_b < v.size_b && v.i_sub_b < v.size_sub)
			{
				push_left(s, save, &v);
				push_right(s, save, &v);
			}
			empty_a(s, save, &v);
			empty_b(s, save, &v);
			v.i_list = (v.i_list + 1) % 2;
		}
		v.size_sub *= 2;
	}
	free_list(&v.a);
	free_list(&v.b);
	return (s->nb_operations);
}

int		initialize(t_push_swap *s, int save, t_merge_sort *v)
{
	int			i;
	t_list_elem	*elem;

	initialize_list(&v->a);
	initialize_list(&v->b);
	i = 0;
	while (i < s->nb_numbers)
	{
		if ((elem = create_list_elem(s->numbers[i++])) == NULL)
		{
			free_list(&v->a);
			return (PS_ERROR);
		}
		add_first(&v->a, elem);
	}
	i = 0;
	while (i++ < s->nb_numbers / 2)
	{
		push(&v->a, &v->b);
		do_operation(s, save, pb);
	}
	v->size_sub = 1;
	return (0);
}

void	set_indexes(t_merge_sort *v)
{
	v->size_a = v->a.size;
	v->size_b = v->b.size;
	v->i_a = 0;
	v->i_b = 0;
	v->i_list = 0;
}
