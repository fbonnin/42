/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:45:05 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 20:47:31 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			(*sort_functions[5])(struct s_push_swap *, int);
	int			nb_sort_functions;
	int			min_nb_operations;
	int			i_min;
	t_operation *operations;
	int			nb_operations;
	t_operation	*compressed_operations;
	int			nb_compressed_operations;
	t_operation	compressed_operation;
	int			i;
}				t_push_swap;

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

int				get_numbers(int argc, char **argv, t_push_swap *s);
int				check_duplicates(t_push_swap *s);

void			copy_numbers(t_push_swap *s);
void			do_operation(t_push_swap *s, int save, t_operation operation);
void			compress_operations(t_push_swap *s);
void			print_operations(t_push_swap *s);

int				bubble_sort(t_push_swap *s, int save);
int				insertion_sort(t_push_swap *s, int save);
int				insertion_sort_2(t_push_swap *s, int save);
int				merge_sort(t_push_swap *s, int save);
int				selection_sort(t_push_swap *s, int save);
int				sort3(t_push_swap *s, int save);

void			initialize_list(t_list *list);
t_list_elem		*create_list_elem(int number);
void			free_list(t_list *list);
int				list_min(t_list *list);
int				list_sorted(t_list *list);

void			add_first(t_list *list, t_list_elem *elem);
void			add_last(t_list *list, t_list_elem *elem);
void			remove_first(t_list *list);
void			remove_last(t_list *list);

void			swap(t_list *list);
void			push(t_list *list1, t_list *list2);
void			rotate(t_list *list);
void			reverse_rotate(t_list *list);

#endif
