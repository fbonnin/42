/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:27:45 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/26 16:27:47 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_int(int *a, int *b)
{
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

int			sort3(t_push_swap *s, int save)
{
	if (s->nb_numbers != 3)
		s->nb_operations = 2000000000;
	else
	{
		if (s->numbers2[0] >= s->numbers2[1] &&
		s->numbers2[0] > s->numbers2[2])
		{
			swap_int(&s->numbers2[0], &s->numbers2[1]);
			swap_int(&s->numbers2[1], &s->numbers2[2]);
			do_operation(s, save, ra);
		}
		else if (s->numbers2[1] > s->numbers2[2])
		{
			swap_int(&s->numbers2[1], &s->numbers2[2]);
			swap_int(&s->numbers2[0], &s->numbers2[1]);
			do_operation(s, save, rra);
		}
		if (s->numbers2[0] > s->numbers2[1])
			do_operation(s, save, sa);
	}
	return (s->nb_operations);
}
