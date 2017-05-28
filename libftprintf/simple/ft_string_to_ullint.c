#include "../libft.h"

static unsigned int		ft_digit_to_int(char c)
{
	if (ft_isdigit(c))
		return (c - 48);
	else if (c == 'A')
		return (10);
	else if (c == 'B')
		return (11);
	else if (c == 'C')
		return (12);
	else if (c == 'D')
		return (13);
	else if (c == 'E')
		return (14);
	else if (c == 'F')
		return (15);
	else
		return (1000);
}

unsigned long long int	ft_string_to_ullint(char *s, unsigned int base)
{
	unsigned long long int	result;
	int						i;

	if (base > 16)
		return (0);
	i = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	result = 0;
	while (ft_digit_to_int(s[i]) < base)
	{
		result *= base;
		result += ft_digit_to_int(s[i]);
		i++;
	}
	return (result);
}
