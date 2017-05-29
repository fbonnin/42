#include "stdio.h"
#include "libft.h"
#include "locale.h"

int main()
{
	wchar_t c;
	//setlocale(LC_ALL, "");
	c = 945;
	ft_printf("%lc\n", c);
	printf("%lc\n", c);
	return (0);
}
