#include "ft_printf.h"

void	ft_get_size(t_printf *s)
{
	char *size;

	size = &s->format[s->i_format];
	if (ft_strnequ(size, "hh", 2))
	{
		s->size = -2;
		s->i_format += 2;
	}
	else if (ft_strnequ(size, "ll", 2))
	{
		s->size = 2;
		s->i_format += 2;
	}
	else if (size[0] == 'h')
	{
		s->size = -1;
		s->i_format++;
	}
	else if (size[0] == 'l')
	{
		s->size = 1;
		s->i_format++;
	}
	else
		ft_get_size2(s, size);
}

void	ft_get_size2(t_printf *s)
{
	if (size[0] == 'j')
	{
		s->size = 3;
		s->i_format++;
	}
	else if (size[0] == 'z')
	{
		s->size = 4;
		s->i_format++;
	}
	else
		s->size = 0;
}
