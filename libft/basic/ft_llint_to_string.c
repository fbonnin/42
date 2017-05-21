#include "../libft.h"

char		*ft_lluint_to_string(unsigned long long int n,
unsigned long long int base)
{
	char					*result;
	int						i_result;
	unsigned long long int	power;

	power = 1;
	while (n / power >= base)
	{
		i_result++;
		power *= base;
	}
	result = ft_strnew(i_result);
	i_result = 0;
	while (power > 0)
	{
		result[i_result] = ft_digit(n / power);
		n %= power;
		power /= base;
		i_result++;
	}
	return (result);
}
