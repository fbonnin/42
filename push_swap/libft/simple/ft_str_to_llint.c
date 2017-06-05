#include "../libft.h"

long long int	ft_str_to_llint(char *s)
{
	long long int	result;
	int				i;
	int				sign;

	i = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(s[i]))
	{
		result *= 10;
		result += s[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}
