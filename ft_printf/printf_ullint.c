static void	ft_flag_sharp(t_printf *s)
{
	if (s->flag_sharp && s->ullint != 0)
	{
		if (s->base == 8)
		{
			s->prefix[0] = '0';
			s->len_prefix = 1;
		}
		else if (s->base == 16)
		{
			s->prefix[0] = '0';
			s->prefix[1] = (uppercase ? 'X' : 'x');
			s->len_prefix = 2;
		}
	}
}

static void	ft_width(t_printf *s)
{
	int i;

	if (!s->flag_minus)
	{
		if (s->flag_zero && s->precision == -1)
			s->nb_zeroes = ft_max(s->width - (s->len_prefix + s->len_number), 0);
		else
		{
			i = 0;
			while (s->len_prefix + s->nb_zeros + s->len_number + i < s->width)
			{
				if (ft_putchar_to_buffer(' ') == PRINTF_ERROR)
					return (PRINTF_ERROR);
				i++;
			}
		}
	}
	return (0);
}

static void	ft_flag_minus(t_printf *s)
{
	int i;

	if (s->flag_minus)
	{
		i = 0;
		while (s->len_prefix + s->nb_zeros + s->len_number + i < s->width)
		{
			if (ft_putchar_to_buffer(' ') == PRINTF_ERROR)
				return (PRINTF_ERROR);
			i++;
		}
	}
	return (0);
}
