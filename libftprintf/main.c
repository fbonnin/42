#include "stdio.h"
#include "libft.h"
#include "locale.h"

int main()
{
	wchar_t c;
	//setlocale(LC_ALL, "");
	c = 128;
	printf("ft returned : %d\n", ft_printf("ft : %S\n", L"é"));
	printf("std returned : %d\n", printf("std : %S\n", L"é"));
	return (0);
}
