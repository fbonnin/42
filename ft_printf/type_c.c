#include "ft_printf.h"

static int	ft_width(t_printf *s)
{
	int i;

	i = 0;
	while (i < s->width - 1)
	{
		if (ft_putchar_to_buffer(' ') == PRINTF_ERROR)
			return (PRINTF_ERROR);
		i++;
	}
	return (0);
}

int			ft_printf_c(t_printf *s)
{
	int i;

	if (!s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	if (ft_putchar_to_buffer(s->c) == PRINTF_ERROR)
		return (PRINTF_ERROR);
	if (s->flag_minus)
		if (ft_width(s) == PRINTF_ERROR)
			return (PRINTF_ERROR);
	return (0);
}

int			ft_type_c(t_printf *s)
{
	if (s->type != 'c' && s->type != 'C')
		return (0);
	if (s->type == 'C' || s->type == 1)
		s->c = va_arg(s->params, wint_t);
	else
		s->c = va_arg(s->params, int);
	return (ft_printf_c(s));
}
