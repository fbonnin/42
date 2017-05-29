#include "stdio.h"
#include "libft.h"
#include "locale.h"
int main()
{
	wchar_t c;
	setlocale(LC_CTYPE, "en_US.UTF-8");
	c = 128;
	printf("\nft returned : %d\n", ft_printf("%2.1S", L"Jambon"));
	printf("\nstd returned : %d\n", printf("%2.1S", L"Jambon"));
	return (0);
}
