#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

# define PS_ERROR -1

typedef enum	e_operation
{
	sa, sb, ss,
	pa, pb,
	ra, rb, rr,
	rra, rrb, rrr
}				t_operation;

typedef struct	s_push_swap
{
	int			*numbers;
	int			nb_numbers;
	int			*numbers2;
	t_operation *operations;
	int			nb_operations;
}				t_push_swap;

int				check_args(int argc, char **argv);
int				get_numbers(int argc, char **argv, t_push_swap *s);
int				check_duplicates(t_push_swap *s);

void			do_operation(t_push_swap *s, int save, t_operation operation);

int				bubble_sort(t_push_swap *s, int save);
int				insertion_sort(t_push_swap *s, int save);

#endif
