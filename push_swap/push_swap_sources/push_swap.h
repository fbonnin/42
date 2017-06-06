#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

# define PS_ERROR -1

typedef struct	s_list_elem
{
	int					number;
	struct s_list_elem	*previous;
	struct s_list_elem	*next;
}				t_list_elem;

typedef struct	s_list
{
	t_list_elem		*first;
	t_list_elem		*last;
	unsigned int	size;
}				t_list;

void			initialize_list(t_list *list);
t_list_elem		*create_list_elem(int number);
void			free_list(t_list *list);

void			add_first(t_list *list, t_list_elem *elem);
void			add_last(t_list *list, t_list_elem *elem);
void			remove_first(t_list *list);
void			remove_last(t_list *list);

void			swap(t_list *list);
void			push(t_list *list1, t_list *list2);
void			rotate(t_list *list);
void			reverse_rotate(t_list *list);

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
int				merge_sort(t_push_swap *s, int save);

#endif
