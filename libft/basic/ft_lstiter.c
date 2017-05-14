/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:28:51 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/10 18:06:08 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *elem;
	t_list *next;

	if (f == NULL)
		return ;
	elem = lst;
	while (elem != NULL)
	{
		next = elem->next;
		f(elem);
		elem = next;
	}
}
