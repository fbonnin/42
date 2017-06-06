#include "push_swap.h"

typedef struct	s_merge_sort
{
	t_list	a;
	t_list	b;
	int		i;
	int		size_sub;
	int		i_list;
	int		size_a;
	int		i_a;
	int		i_sub_a;
	int		size_b;
	int		i_b;
	int		i_sub_b;
}				t_merge_sort;

int	merge_sort(t_push_swap *s, int save)
{
	t_merge_sort v;

	initialize_list(&v.a);
	initialize_list(&v.b);
	v.i = 0;
	while (v.i < s->nb_numbers)
		add_first(&v.a, create_list_elem(s->numbers[v.i++]));
	v.i = 0;
	while (v.i++ < s->nb_numbers / 2)
	{
		push(&v.a, &v.b);
		do_operation(s, save, pb);
	}
	v.size_sub = 1;
	while (v.size_sub < s->nb_numbers)
	{
		v.size_a = v.a.size;
		v.size_b = v.b.size;
		v.i_a = 0;
		v.i_b = 0;
		v.i_list = 0;
		while (v.i_a < v.size_a)
		{
			v.i_sub_a = 0;
			v.i_sub_b = 0;
			while (v.i_a < v.size_a && v.i_sub_a < v.size_sub && v.i_b < v.size_b && v.i_sub_b < v.size_sub)
			{
				if (v.i_list == 0)
				{
					if (v.a.last->number < v.b.last->number)
					{
						v.i_a++;
						v.i_sub_a++;
					}
					else
					{
						push(&v.b, &v.a);
						do_operation(s, save, pa);
						v.i_b++;
						v.i_sub_b++;
					}
					rotate(&v.a);
					do_operation(s, save, ra);
				}
				else
				{
					if (v.a.last->number < v.b.last->number)
					{
						push(&v.a, &v.b);
						do_operation(s, save, pb);
						v.i_a++;
						v.i_sub_a++;
					}
					else
					{
						v.i_b++;
						v.i_sub_b++;
					}
					rotate(&v.b);
					do_operation(s, save, rb);
				}
			}
			while (v.i_a < v.size_a && v.i_sub_a < v.size_sub)
			{
				if (v.i_list == 0)
				{
					rotate(&v.a);
					do_operation(s, save, ra);
				}
				else
				{
					push(&v.a, &v.b);
					do_operation(s, save, pb);
					rotate(&v.b);
					do_operation(s, save, rb);
				}
				v.i_a++;
				v.i_sub_a++;
			}
			while (v.i_b < v.size_b && v.i_sub_b < v.size_sub)
			{
				if (v.i_list == 0)
				{
					push(&v.b, &v.a);
					do_operation(s, save, pa);
					rotate(&v.a);
					do_operation(s, save, ra);
				}
				else
				{
					rotate(&v.b);
					do_operation(s, save, rb);
				}
				v.i_b++;
				v.i_sub_b++;
			}
			v.i_list = (v.i_list + 1) % 2;
		}
		v.size_sub *= 2;
	}
	free_list(&v.a);
	free_list(&v.b);
	return (s->nb_operations);
}
