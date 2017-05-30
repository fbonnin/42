#include "../libft.h"

static int	ft_byte4(t_printf *s)
{
	if (s->nb_bits > 16)
	{
		s->i_bit = s->nb_bits - 1 - 18;
		s->i_utf8 = 7;
		if (s->nb_bits > 21)
		{
			ft_strcpy(s->utf8, "10000000");
			while (s->i_utf8 >= 2)
				s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
		}
		else
		{
			ft_strcpy(s->utf8, "11110000");
			while (s->i_bit >= 0)
				s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
		}
		s->buffer[s->i_buffer++] = ft_string_to_ullint(s->utf8, 2);
	}
	return (0);
}

static int	ft_byte3(t_printf *s)
{
	if (s->nb_bits > 11)
	{
		s->i_bit = s->nb_bits - 1 - 12;
		s->i_utf8 = 7;
		if (s->nb_bits > 16)
		{
			ft_strcpy(s->utf8, "10000000");
			while (s->i_utf8 >= 2)
				s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
		}
		else
		{
			ft_strcpy(s->utf8, "11100000");
			while (s->i_bit >= 0)
				s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
		}
		s->buffer[s->i_buffer++] = ft_string_to_ullint(s->utf8, 2);
	}
	return (0);
}

static int	ft_byte2(t_printf *s)
{
	if (s->nb_bits > 7)
	{
		s->i_bit = s->nb_bits - 1 - 6;
		s->i_utf8 = 7;
		if (s->nb_bits > 11)
		{
			ft_strcpy(s->utf8, "10000000");
			while (s->i_utf8 >= 2)
				s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
		}	
		else
		{
			ft_strcpy(s->utf8, "11000000");
			while (s->i_bit >= 0)
				s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
		}
		s->buffer[s->i_buffer++] = ft_string_to_ullint(s->utf8, 2);
	}
	return (0);
}

static int	ft_byte1(t_printf *s)
{
	s->i_bit = s->nb_bits - 1;
	s->i_utf8 = 7;
	if (s->nb_bits > 7)
	{
		ft_strcpy(s->utf8, "10000000");
		while (s->i_utf8 >= 2)
			s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
	}	
	else
	{
		ft_strcpy(s->utf8, "00000000");
		while (s->i_bit >= 0)
			s->utf8[s->i_utf8--] = s->bits[s->i_bit--];
	}
	s->buffer[s->i_buffer++] = ft_string_to_ullint(s->utf8, 2);
	return (0);
}

int			ft_put_utf8_to_buffer(t_printf *s)
{
	if (ft_byte4(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (ft_byte3(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (ft_byte2(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (ft_byte1(s) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	return (0);
}
