/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_unknown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:29:16 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/26 18:45:44 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_type_unknown(t_printf *s)
{
	if (s->type == 'c' || s->type == 'C' ||
		s->type == 's' || s->type == 'S' ||
		s->type == 'u' || s->type == 'U' ||
		s->type == 'o' || s->type == 'O' ||
		s->type == 'x' || s->type == 'X' ||
		s->type == 'p' || s->type == 'b' ||
		s->type == 'd' || s->type == 'D' ||
		s->type == 'i' || s->type == 'n' ||
		s->type == '%')
		s->i_format++;
}
