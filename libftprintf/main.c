#include "stdio.h"
#include "libft.h"
#include "locale.h"
int main()
{
	wchar_t c;
	setlocale(LC_CTYPE, "en_US.UTF-8");
	c = 128;
	printf("\nft returned : %d\n", ft_printf("{%30S}", L"我是一只猫。"));
	printf("\nstd returned : %d\n", printf("{%30S}", L"我是一只猫。"));
	return (0);
}
