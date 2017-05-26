/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:58:05 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/26 20:37:17 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar_to_buffer(t_printf *s, char c)
{
	s->buffer[s->i_buffer++] = c;
	if (s->i_buffer == PRINTF_BUFFER_SIZE)
	{
		if (write(1, s->buffer, PRINTF_BUFFER_SIZE) == -1)
			return (PRINTF_ERROR);
		s->i_buffer = 0;
	}
	s->nb_chars_written++;
	return (0);
}

int	ft_putstr_to_buffer(t_printf *s, char *str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		if (ft_putchar_to_buffer(s, str[i++]) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	return (0);
}

int	ft_convert(t_printf *s)
{
	s->len_prefix = 0;
	ft_get_flags(s);
	while (ft_isdigit(s->format[s->i_format]) || s->format[s->i_format] == '*')
		if (ft_get_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	if (ft_get_precision(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	ft_get_size(s);
	s->type = s->format[s->i_format];
	if (ft_type_c(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (ft_type_str(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (ft_type_uint(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (ft_type_int(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	ft_type_n(s);
	ft_type_unknown(s);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	t_printf s;

	if (format == NULL)
		return (PRINTF_ERROR);
	s.format = format;
	s.i_format = 0;
	va_start(s.params, format);
	s.nb_chars_written = 0;
	s.i_buffer = 0;
	while (format[s.i_format] != 0)
	{
		while (format[s.i_format] != '%' && format[s.i_format] != 0)
			if (ft_putchar_to_buffer(&s, format[s.i_format++]) == PRINTF_ERROR)
				return (PRINTF_ERROR);
		if (format[s.i_format++] == 0)
			break ;
		if (ft_convert(&s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	}
	va_end(s.params);
	write(1, s.buffer, s.i_buffer);
	return (s.nb_chars_written);
}
