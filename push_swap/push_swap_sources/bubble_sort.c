/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:05:31 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 18:05:32 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	bubble_sort(t_push_swap *s, int save)
{
	int sorted;
	int i;
	int t;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (i < s->nb_numbers - 1)
		{
			if (s->numbers2[i] > s->numbers2[i + 1])
			{
				sorted = 0;
				t = s->numbers2[i];
				s->numbers2[i] = s->numbers2[i + 1];
				s->numbers2[i + 1] = t;
				do_operation(s, save, sa);
			}
			i++;
			do_operation(s, save, ra);
		}
		do_operation(s, save, ra);
	}
	return (s->nb_operations);
}
