#include "libft.h"

int main()
{
	ft_printf("{%05.*d}", -15, 42);
	//ft_printf("{%3*p}", 10, 0);
	//ft_printf("%05.s", "A");
	//ft_printf("{%05.c}", 0);
	ft_putendl("");
	printf("{%05.*d}", -15, 42);
	//printf("{%3*p}", 10, 0);
	//printf("%05.s", "A");
	//printf("{%05.c}", 0);
	return (0);
}
