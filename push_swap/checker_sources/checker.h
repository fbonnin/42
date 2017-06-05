#ifndef CHECKER_H
# define CHECKER_H

# include "../libft/libft.h"

# define CHECK_ERROR -1

int				check_args(int argc, char **argv);
int				get_numbers(int argc, char **argv, int **numbers);
int				check_duplicates(int *numbers, int nb_numbers);

typedef struct	s_list_elem
{
	int					number;
	struct s_list_elem	*previous;
	struct s_list_elem	*next;
}				t_list_elem;

typedef struct	s_list2
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

int				numbers_to_a(int *numbers, int nb_numbers, t_list *a);
int				do_operations(t_list *a, t_list *b, char *line);
int				do_operations_2(t_list *a, t_list *b, char *line);
int				check_result(t_list *a, t_list *b);

#endif
