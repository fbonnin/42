/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:24:36 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/26 15:07:30 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_width(t_printf *s)
{
	int i;

	i = 0;
	while (i < s->width - 1)
	{
		if (ft_putchar_to_buffer(s, ' ') == PRINTF_ERROR)
			return (PRINTF_ERROR);
		i++;
	}
	return (0);
}

int			ft_printf_c(t_printf *s)
{
	if (!s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	if (ft_putchar_to_buffer(s, s->c) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	return (0);
}

int			ft_type_c(t_printf *s)
{
	if (s->type != 'c' && s->type != 'C' && s->type != '%')
		return (0);
	if (s->type == '%')
		s->c = 37;
	else if (s->type == 'C' || s->type == 1)
		s->c = va_arg(s->params, wint_t);
	else
		s->c = va_arg(s->params, int);
	return (ft_printf_c(s));
}
