#include "../libft.h"

static char	ft_digit(unsigned int digit, int uppercase)
{
	if (digit <= 9)
		return (digit + 48);
	if (digit == 10)
		return (uppercase ? 'A' : 'a');
	if (digit == 11)
		return (uppercase ? 'B' : 'b');
	if (digit == 12)
		return (uppercase ? 'C' : 'c');
	if (digit == 13)
		return (uppercase ? 'D' : 'd');
	if (digit == 14)
		return (uppercase ? 'E' : 'e');
	return (uppercase ? 'F' : 'f');
}

char		*ft_ullint_to_string(unsigned long long int n,
unsigned long long int base, int uppercase)
{
	char					*result;
	int						i_result;
	unsigned long long int	power;

	if (base > 16)
		return (NULL);
	i_result = 0;
	power = 1;
	while (n / power >= base)
	{
		i_result++;
		power *= base;
	}
	if ((result = ft_strnew(i_result)) == NULL)
		return (NULL);
	i_result = 0;
	while (power > 0)
	{
		result[i_result] = ft_digit(n / power, uppercase);
		n %= power;
		power /= base;
		i_result++;
	}
	return (result);
}
