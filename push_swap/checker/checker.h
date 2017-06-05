#ifndef CHECKER_H
# define CHECKER_H

typedef struct	s_list_elem
{
	int			number;
	t_list_elem	*previous;
	t_list_elem	*next;
}				t_list_elem;

typedef struct	s_list
{
	t_list_elem		*first;
	t_list_elem		*last;
	unsigned int	size;
}				t_list;

#endif
