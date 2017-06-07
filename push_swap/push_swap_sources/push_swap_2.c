/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 18:30:41 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 20:30:18 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void		compress_operations(t_push_swap *s)
{
	s->nb_compressed_operations = 0;
	s->i = 0;
	while (s->i < s->nb_operations - 1)
	{
		if ((s->operations[s->i] == sa && s->operations[s->i + 1] == sb)
		|| (s->operations[s->i] == sb && s->operations[s->i + 1] == sa))
			s->compressed_operation = ss;
		else if ((s->operations[s->i] == ra && s->operations[s->i + 1] == rb)
		|| (s->operations[s->i] == rb && s->operations[s->i + 1] == ra))
			s->compressed_operation = rr;
		else if ((s->operations[s->i] == rra && s->operations[s->i + 1] == rrb)
		|| (s->operations[s->i] == rrb && s->operations[s->i + 1] == rra))
			s->compressed_operation = rrr;
		else
		{
			s->compressed_operation = s->operations[s->i];
			s->i--;
		}
		s->compressed_operations[s->nb_compressed_operations++] =
		s->compressed_operation;
		s->i += 2;
	}
	if (s->i == s->nb_operations - 1)
		s->compressed_operations[s->nb_compressed_operations++] =
		s->operations[s->i];
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
	while (i < s->nb_compressed_operations)
	{
		print_operation(s->compressed_operations[i++]);
		ft_printf("\n");
	}
}
