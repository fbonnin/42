/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:58:05 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/29 20:47:14 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			ft_put_wchar_to_buffer(t_printf *s, unsigned int c, int w)
{
	if (!w || MB_CUR_MAX == 1)
	{
		if (c > 255)
			return (PRINTF_ERROR);
		s->buffer[s->i_buffer++] = c;
	}
	else
	{
		if ((s->bits = ft_ullint_to_str(c, 2, 0)) == NULL)
			return (PRINTF_ERROR);
		if ((s->nb_bits = ft_strlen(s->bits)) > 21)
			return (PRINTF_ERROR);
		if (ft_put_utf8_to_buffer(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	}
	if (s->i_buffer > PRINTF_BUFFER_SIZE - 4)
	{
		if (write(1, s->buffer, s->i_buffer) == -1)
			return (PRINTF_ERROR);
		s->nb_bytes_written += s->i_buffer;
		s->i_buffer = 0;
	}
	s->nb_chars_written++;
	return (0);
}

static int	ft_convert(t_printf *s)
{
	s->len_prefix = 0;
	s->nb_zeroes = 0;
	ft_get_flags(s);
	s->width = -1;
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
	if (ft_type_unknown(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	s->i_format++;
	return (0);
}

int			ft_printf(const char *format, ...)
{
	t_printf s;

	if (format == NULL)
		return (PRINTF_ERROR);
	s.format = format;
	s.i_format = 0;
	va_start(s.params, format);
	s.nb_bytes_written = 0;
	s.nb_chars_written = 0;
	s.i_buffer = 0;
	while (format[s.i_format] != 0)
	{
		while (format[s.i_format] != '%' && format[s.i_format] != 0)
			if (ft_put_wchar_to_buffer(&s, format[s.i_format++], 0) ==
			PRINTF_ERROR)
				return (PRINTF_ERROR);
		if (format[s.i_format++] == 0)
			break ;
		if (ft_convert(&s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	}
	va_end(s.params);
	write(1, s.buffer, s.i_buffer);
	s.nb_bytes_written += s.i_buffer;
	return (s.nb_bytes_written);
}
