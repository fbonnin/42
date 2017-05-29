#include "../libft.h"

static int	ft_unicode4(t_printf *s)
{
	if (s->nb_bits > 16)
	{
		s->i_bit = s->nb_bits - 1 - 18;
		s->i_unicode = 7;
		if (s->nb_bits > 21)
		{
			ft_strcpy(s->unicode, "10000000");
			while (s->i_unicode >= 2)
				s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
		}
		else
		{
			ft_strcpy(s->unicode, "11110000");
			while (s->i_bit >= 0)
				s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
		}
		s->buffer[s->i_buffer++] = ft_string_to_ullint(s->unicode, 2);
	}
	return (0);
}

static int	ft_unicode3(t_printf *s)
{
	if (s->nb_bits > 11)
	{
		s->i_bit = s->nb_bits - 1 - 12;
		s->i_unicode = 7;
		if (s->nb_bits > 16)
		{
			ft_strcpy(s->unicode, "10000000");
			while (s->i_unicode >= 2)
				s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
		}
		else
		{
			ft_strcpy(s->unicode, "11100000");
			while (s->i_bit >= 0)
				s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
		}
		s->buffer[s->i_buffer++] = ft_string_to_ullint(s->unicode, 2);
	}
	return (0);
}

static int	ft_unicode2(t_printf *s)
{
	if (s->nb_bits > 7)
	{
		s->i_bit = s->nb_bits - 1 - 6;
		s->i_unicode = 7;
		if (s->nb_bits > 11)
		{
			ft_strcpy(s->unicode, "10000000");
			while (s->i_unicode >= 2)
				s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
		}	
		else
		{
			ft_strcpy(s->unicode, "11000000");
			while (s->i_bit >= 0)
				s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
		}
		s->buffer[s->i_buffer++] = ft_string_to_ullint(s->unicode, 2);
	}
	return (0);
}

static int	ft_unicode1(t_printf *s)
{
	s->i_bit = s->nb_bits - 1;
	s->i_unicode = 7;
	if (s->nb_bits > 7)
	{
		ft_strcpy(s->unicode, "10000000");
		while (s->i_unicode >= 2)
			s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
	}	
	else
	{
		ft_strcpy(s->unicode, "00000000");
		while (s->i_bit >= 0)
			s->unicode[s->i_unicode--] = s->bits[s->i_bit--];
	}
	s->buffer[s->i_buffer++] = ft_string_to_ullint(s->unicode, 2);
	return (0);
}

int			ft_putwchar_to_buffer(t_printf *s, unsigned int c, int w)
{
	if (!w)
	{
		s->buffer[s->i_buffer++] = c;
	}
	else{
	if (MB_CUR_MAX == 1)
	{
		if (c > 255)
		{
			//write(1, s->buffer, s->i_buffer);
			return (PRINTF_ERROR);
		}
		s->buffer[s->i_buffer++] = c;
	}
	else
	{
		if ((s->bits = ft_ullint_to_string(c, 2, 0)) == NULL)
			return (PRINTF_ERROR);
		if ((s->nb_bits = ft_strlen(s->bits)) > 21)
			return (PRINTF_ERROR);
		ft_unicode4(s);
		ft_unicode3(s);
		ft_unicode2(s);
		ft_unicode1(s);
	}}
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
