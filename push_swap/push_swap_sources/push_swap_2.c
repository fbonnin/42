/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:30:41 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 19:51:49 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			get_input(int argc, char **argv, t_push_swap *s)
{
	if (get_numbers(argc, argv, s) == PS_ERROR)
		return (PS_ERROR);
	if (check_duplicates(s) == PS_ERROR)
	{
		free(s->numbers);
		return (PS_ERROR);
	}
	if ((s->numbers2 = malloc(s->nb_numbers * sizeof(int))) == NULL)
	{
		free(s->numbers);
		return (PS_ERROR);
	}
	return (0);
}

void		copy_numbers(t_push_swap *s)
{
	int i;

	i = 0;
	while (i < s->nb_numbers)
	{
		s->numbers2[i] = s->numbers[i];
		i++;
	}
}

void		do_operation(t_push_swap *s, int save, t_operation operation)
{
	if (save)
		s->operations[s->nb_operations] = operation;
	s->nb_operations++;
}

static void	print_operation(t_operation operation)
{
	if (operation == sa)
		ft_printf("sa");
	else if (operation == sb)
		ft_printf("sb");
	else if (operation == ss)
		ft_printf("ss");
	else if (operation == pa)
		ft_printf("pa");
	else if (operation == pb)
		ft_printf("pb");
	else if (operation == ra)
		ft_printf("ra");
	else if (operation == rb)
		ft_printf("rb");
	else if (operation == rr)
		ft_printf("rr");
	else if (operation == rra)
		ft_printf("rra");
	else if (operation == rrb)
		ft_printf("rrb");
	else if (operation == rrr)
		ft_printf("rrr");
}

void		print_operations(t_push_swap *s)
{
	int			i;

	i = 0;
	while (i < s->nb_operations)
	{
		print_operation(s->operations[i++]);
		ft_printf("\n");
	}
}
