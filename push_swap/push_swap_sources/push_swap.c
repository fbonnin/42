/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 20:28:52 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 20:42:00 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_input(int argc, char **argv, t_push_swap *s)
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

static void	find_min(t_push_swap *s)
{
	int i;

	s->min_nb_operations = 2000000000;
	i = 0;
	while (i < s->nb_sort_functions)
	{
		copy_numbers(s);
		s->nb_operations = 0;
		s->sort_functions[i](s, 0);
		if (s->nb_operations < s->min_nb_operations)
		{
			s->min_nb_operations = s->nb_operations;
			s->i_min = i;
		}
		i++;
	}
}

void		print_algo_name(int i)
{
	if (i == 0)
		ft_printf("Bubble sort :\n");
	else if (i == 1)
		ft_printf("Insertion sort :\n");
	else if (i == 2)
		ft_printf("Merge sort :\n");
}

int			main(int argc, char **argv)
{
	t_push_swap s;

	if (argc < 2)
		return (0);
	if (get_input(argc, argv, &s) == PS_ERROR)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	s.sort_functions[0] = &bubble_sort;
	s.sort_functions[1] = &insertion_sort;
	s.sort_functions[2] = &merge_sort;
	s.nb_sort_functions = 3;
	find_min(&s);
	s.operations = malloc(s.min_nb_operations * sizeof(t_operation));
	copy_numbers(&s);
	s.nb_operations = 0;
	s.sort_functions[s.i_min](&s, 1);
	print_algo_name(s.i_min);
	print_operations(&s);
	free(s.numbers);
	free(s.numbers2);
	return (0);
}
