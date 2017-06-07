#include "push_swap.h"

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
	int i;

	if (get_input(argc, argv, &s) == PS_ERROR)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	s.sort_functions[0] = &bubble_sort;
	s.sort_functions[1] = &insertion_sort;
	s.sort_functions[2] = &merge_sort;
	s.min_nb_operations = 2000000000; // oo
	i = 0;
	while (i < 3)
	{
		copy_numbers(&s);
		s.nb_operations = 0;
		s.sort_functions[i](&s, 0);
		if (s.nb_operations < s.min_nb_operations)
		{
			s.min_nb_operations = s.nb_operations;
			s.i_min = i;
		}
		i++;
	}
	s.operations = malloc(s.min_nb_operations * sizeof(t_operation));
	copy_numbers(&s);
	s.nb_operations = 0;
	s.sort_functions[s.i_min](&s, 1);
	//print_algo_name(i_min);
	print_operations(&s);
	free(s.numbers);
	free(s.numbers2);
}
