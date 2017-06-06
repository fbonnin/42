#include "push_swap.h"

int	merge_sort(t_push_swap *s, int save)
{
	t_list a;
	t_list b;
	int i;
	int size_sub;
	int i_a, i_sub_a, size_a;
	int i_b, i_sub_b, size_b;
	int i_mod;

	initialize_list(&a);
	initialize_list(&b);
	i = 0;
	while (i < s->nb_numbers)
		add_first(&a, create_list_elem(s->numbers[i++]));
	i = 0;
	while (i++ < s->nb_numbers / 2)
	{
		push(&a, &b);
		do_operation(s, save, pb);
	}
	size_sub = 1;
	while (size_sub < s->nb_numbers)
	{
		size_a = a.size;
		size_b = b.size;
		i_a = 0;
		i_b = 0;
		i_mod = 0;
		while (i_a < size_a)
		{
			i_sub_a = 0;
			i_sub_b = 0;
			while (i_a < size_a && i_sub_a < size_sub && i_b < size_b && i_sub_b < size_sub)
			{
				if (i_mod == 0)
				{
					if (a.last->number < b.last->number)
					{
						i_a++;
						i_sub_a++;
					}
					else
					{
						push(&b, &a);
						do_operation(s, save, pa);
						i_b++;
						i_sub_b++;
					}
					rotate(&a);
					do_operation(s, save, ra);
				}
				else
				{
					if (a.last->number < b.last->number)
					{
						push(&a, &b);
						do_operation(s, save, pb);
						i_a++;
						i_sub_a++;
					}
					else
					{
						i_b++;
						i_sub_b++;
					}
					rotate(&b);
					do_operation(s, save, rb);
				}
			}
			while (i_a < size_a && i_sub_a < size_sub)
			{
				if (i_mod == 0)
				{
					rotate(&a);
					do_operation(s, save, ra);
				}
				else
				{
					push(&a, &b);
					do_operation(s, save, pb);
					rotate(&b);
					do_operation(s, save, rb);
				}
				i_a++;
				i_sub_a++;
			}
			while (i_b < size_b && i_sub_b < size_sub)
			{
				if (i_mod == 0)
				{
					push(&b, &a);
					do_operation(s, save, pa);
					rotate(&a);
					do_operation(s, save, ra);
				}
				else
				{
					rotate(&b);
					do_operation(s, save, rb);
				}
				i_b++;
				i_sub_b++;
			}
			i_mod = (i_mod + 1) % 2;
		}
		size_sub *= 2;
	}


	free_list(&a);
	free_list(&b);
	return (s->nb_operations);
}
