/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:28:19 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/26 14:28:22 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_wstrlen(wchar_t *wstr)
{
	int len;

	len = 0;
	while (wstr[len] != 0)
		len++;
	return (len);
}

static int	ft_width(t_printf *s)
{
	int i;

	i = 0;
	while (s->len_str + i < s->width)
	{
		if (ft_putchar_to_buffer(s, ' ') == PRINTF_ERROR)
			return (PRINTF_ERROR);
		i++;
	}
	return (0);
}

int			ft_printf_str(t_printf *s)
{
	int i;

	s->len_str = ft_strlen(s->str);
	if (s->precision > -1)
		s->len_str = ft_min(s->len_str, s->precision);
	if (!s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	i = 0;
	while (i < s->len_str)
		if (ft_putchar_to_buffer(s, s->str[i++]) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	if (s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	return (0);
}

int			ft_printf_wstr(t_printf *s)
{
	int i;

	s->len_str = ft_wstrlen(s->wstr);
	if (s->precision > -1)
		s->len_str = ft_min(s->len_str, s->precision);
	if (!s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	i = 0;
	while (i < s->len_str)
		if (ft_putchar_to_buffer(s, s->wstr[i++]) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	if (s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	return (0);
}

int			ft_type_str(t_printf *s)
{
	if (s->type != 's' && s->type != 'S')
		return (0);
	if (s->type == 'S' || s->size == 1)
	{
		s->wstr = va_arg(s->params, wchar_t *);
		if (ft_printf_wstr(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	}
	else
	{
		s->str = va_arg(s->params, char *);
		if (ft_printf_str(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	}
	return (0);
}
