#include "../libft.h"

int	ft_type_unknown(t_printf *s)
{
	if (s->type == 'c' || s->type == 'C' ||
		s->type == 's' || s->type == 'S' ||
		s->type == 'u' || s->type == 'U' ||
		s->type == 'o' || s->type == 'O' ||
		s->type == 'x' || s->type == 'X' ||
		s->type == 'p' || s->type == 'b' ||
		s->type == 'd' || s->type == 'D' ||
		s->type == 'i' || s->type == 'n')
	{
		s->i_format++;
		return (0);
	}
	return (ft_putchar_to_buffer(s, '%'));
}
