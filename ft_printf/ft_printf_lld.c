static void	ft_flags_plus_space(printf_s *s)
{
	if (s->llint >= 0)
	{
		if (s->flag_plus)
			s->added_chars[s->nb_added_chars++] = '+';
		else
			s->added_chars[s->nb_added_chars++] = ' ';
	}
}

static void	ft_precision(printf_s *s)
{
	s->i = 0;
	while (s->len + s->i < s->precision)
		s->added_chars[s->nb_added_chars++] = '0';
}

static void	ft_width(printf_s *s)
{
	if (!s->flag_minus)
	{
		if (s->flag_0 && s->precision == -1)
			while (s->len + s->nb_added_chars < s->width)
				s->added_chars[s->nb_added_chars++] = '0';
		else
		{
			s->i = 0;
			while (s->len + s->nb_added_chars + s->i < s->width)
			{
				ft_putchar_to_buffer(' ');
				s->i++;
			}
		}
	}
}

static void	ft_flag_minus(printf_s *s)
{
	if (s->flag_minus)
	{
		i = 0;
		while (s->len + s->nb_added_chars + s->i < s->width)
		{
			ft_putchar_to_buffer(' ');
			i++;
		}
	}
}

int			ft_printf_lld(printf_s *s)
{
	if ((s->str = ft_llint_to_str(s->llint)) == NULL)
		return (-1);
	s->len = ft_strlen(str);
	s->nb_added_chars = 0;
	ft_flags_plus_space(s);
	ft_precision(s);
	ft_width(s);
	s->i = 0;
	while (s->i < s->nb_added_chars)
	{
		ft_putchar_to_buffer(s->added_chars[i]);
		s->i++;
	}
	s->i = 0;
	while (s->str[s->i] != 0)
	{
		putchar_to_buffer(s->str[s->i]);
		s->i++;
	}
	ft_flag_minus(s);
}
