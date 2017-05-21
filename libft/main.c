#include "stdio.h"
#include "libft.h"

int	main()
{
	unsigned long long int n;
	char *s;

	n = 1000000;
	s = ft_ullint_to_string(n, 2, 1);
	ft_putendl(s);
	free(s);

	s = ft_ullint_to_string(n, 8, 1);
	ft_putendl(s);
	free(s);

	s = ft_ullint_to_string(n, 16, 1);
	ft_putendl(s);
	free(s);

	return (0);
}
