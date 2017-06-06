#include "push_swap.h"

int	insertion_sort(t_push_swap *s, int save)
{
	int i1;
	int i2;
	int t;

	i1 = 0;
	while (i1 < s->nb_numbers)
	{
		do_operation(s, save, pb);
		i2 = i1;
		while (i2 > 0)
		{
			if (s->numbers2[i2 - 1] > s->numbers2[i2])
			{
				t = s->numbers2[i2 - 1];
				s->numbers2[i2 - 1] = s->numbers2[i2];
				s->numbers2[i2] = t;
				do_operation(s, save, sb);
			}
			i2--;
			do_operation(s, save, rb);
		}
		do_operation(s, save, rb);
		i1++;
	}
	i1 = 0;
	while (i1++ < s->nb_numbers)
		do_operation(s, save, pa);
	return (s->nb_operations);
}
