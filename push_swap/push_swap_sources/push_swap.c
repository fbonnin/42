#include "push_swap.h"

int		get_input(int argc, char **argv, t_push_swap *s)
{
	if (get_numbers(argc, argv, s) == PS_ERROR)
		return (PS_ERROR);
	s->nb_numbers = argc -1;
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

void	do_operation(t_push_swap *s, int save, t_operation operation)
{
	if (save)
		s->operations[s->nb_operations] = operation;
	s->nb_operations++;
}

void	print_operations(t_push_swap *s)
{
	int			i;
	t_operation	operation;

	i = 0;
	while (i < s->nb_operations)
	{
		operation = s->operations[i++];
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
		ft_printf("\n");
	}
}

void	copy_numbers(t_push_swap *s)
{
	int i;

	i = 0;
	while (i < s->nb_numbers)
	{
		s->numbers2[i] = s->numbers[i];
		i++;
	}
}

void	print_algo_name(int i)
{
	if (i == 0)
		ft_printf("Bubble sort :\n");
	else if (i == 1)
		ft_printf("Insertion sort :\n");
	else if (i == 2)
		ft_printf("Merge sort :\n");
}

int		main(int argc, char **argv)
{
	t_push_swap s;
	int (*sort_functions[3])(t_push_swap *, int);
	int min_nb_operations;
	int i_min;
	int i;

	if (get_input(argc, argv, &s) == PS_ERROR)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	sort_functions[0] = &bubble_sort;
	sort_functions[1] = &insertion_sort;
	sort_functions[2] = &merge_sort;

	min_nb_operations = 2000000000; // oo
	i = 0;
	while (i < 3)
	{
		copy_numbers(&s);
		s.nb_operations = 0;
		sort_functions[i](&s, 0);
		if (s.nb_operations < min_nb_operations)
		{
			min_nb_operations = s.nb_operations;
			i_min = i;
		}
		i++;
	}
	s.operations = malloc(min_nb_operations * sizeof(t_operation));
	copy_numbers(&s);
	s.nb_operations = 0;
	sort_functions[i_min](&s, 1);
	//print_algo_name(i_min);
	print_operations(&s);
	free(s.numbers);
	free(s.numbers2);
}
