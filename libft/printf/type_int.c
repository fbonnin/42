#include "../libft.h"

int	ft_printf_llint(t_printf *s)
{
	if (s->llint >= 0)
	{
		if (s->flag_plus)
		{
			s->prefix[0] = '+';
			s->len_prefix = 1;
		}
		else if (s->flag_space)
		{
			s->prefix[0] = ' ';
			s->len_prefix = 1;
		}
		s->ullint = s->llint;
	}
	else if (s->llint == -9223372036854775807)
		s->ullint = 9223372036854775807;
	else
	{
		s->prefix[0] = '-';
		s->len_prefix = 1;
		s->ullint = -s->llint;
	}
	s->base = 10;
	s->uppercase = 0;
	return (ft_printf_ullint(s));
}

int	ft_type_int(t_printf *s)
{
	if (s->type != 'd' && s->type != 'D' && s->type != 'i')
		return (0);
	if (s->type == 'D')
		s->llint = va_arg(s->params, long int);
	else if (s->size == -2)
		s->llint = va_arg(s->params, /*char*/ int);
	else if (s->size == -1)
		s->llint = va_arg(s->params, /*short*/ int);
	else if (s->size == 0)
		s->llint = va_arg(s->params, int);
	else if (s->size == 1)
		s->llint = va_arg(s->params, long int);
	else if (s->size == 2)
		s->llint = va_arg(s->params, long long int);
	else if (s->size == 3)
		s->llint = va_arg(s->params, intmax_t);
	else if (s->size == 4)
		s->llint = va_arg(s->params, size_t);
	return (ft_printf_llint(s));
}
