#include "../libft.h"

int	ft_type_uint(t_printf *s)
{
	s->uppercase = 0;
	if (s->type == 'u' || s->type == 'U')
		s->base = 10;
	else if (s->type == 'o' || s->type == 'O')
		s->base = 8;
	else if (s->type == 'x' || s->type == 'X' || s->type == 'p')
	{
		s->base = 16;
		if (s->type == 'X')
			s->uppercase = 1;
	}
	else if (s->type == 'b')
		s->base = 2;
	else
		return (0);
	return (ft_type_uint(s));
}

int	ft_type_uint2(t_printf *s)
{
	if (s->type == 'U' || s->type == 'O')
		s->ullint = va_arg(s->params, unsigned long int);
	else if (s->type == 'p')
		s->ullint = (unsigned long long int)va_arg(s->params, void *);
	else if (s->type == -2)
		s->ullint = va_arg(s->params, unsigned /*char*/int);
	else if (s->type == -1)
		s->ullint = va_arg(s->params, unsigned /*short*/ int);
	else if (s->type == 0)
		s->ullint = va_arg(s->params, unsigned int);
	else if (s->type == 1)
		s->ullint = va_arg(s->params, unsigned long int);
	else if (s->type == 2)
		s->ullint = va_arg(s->params, unsigned long long int);
	else if (s->type == 3)
		s->ullint = va_arg(s->params, uintmax_t);
	else if (s->type == 4)
		s->ullint = va_arg(s->params, size_t);
	return (ft_printf_ullint(s));
}
