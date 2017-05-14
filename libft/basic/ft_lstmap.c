/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:31:54 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/10 18:14:45 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *result;
	t_list *elem;
	t_list *next;
	t_list *new_elem;

	result = NULL;
	elem = lst;
	while (elem != NULL)
	{
		next = elem->next;
		new_elem = f(elem);
		if (new_elem == NULL)
			return (NULL);
		ft_lst_push_back(&result, new_elem);
		elem = next;
	}
	return (result);
}
