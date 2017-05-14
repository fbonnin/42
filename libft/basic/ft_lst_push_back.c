/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 20:38:27 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/10 18:13:08 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lst_push_back(t_list **alst, t_list *new)
{
	t_list *elem;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	elem = *alst;
	while (elem->next != NULL)
		elem = elem->next;
	elem->next = new;
}
