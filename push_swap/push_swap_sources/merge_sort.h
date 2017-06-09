/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 15:29:39 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/09 15:29:59 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_SORT_H
# define MERGE_SORT_H

typedef struct	s_merge_sort
{
	t_list	a;
	t_list	b;
	int		size_sub;
	int		size_a;
	int		i_a;
	int		size_b;
	int		i_b;
	int		i_list;
	int		i_sub_a;
	int		i_sub_b;
}				t_merge_sort;

int				initialize(t_push_swap *s, int save, t_merge_sort *v);
void			set_indexes(t_merge_sort *v);
void			push_left(t_push_swap *s, int save, t_merge_sort *v);
void			push_right(t_push_swap *s, int save, t_merge_sort *v);
void			empty_a(t_push_swap *s, int save, t_merge_sort *v);
void			empty_b(t_push_swap *s, int save, t_merge_sort *v);

#endif
