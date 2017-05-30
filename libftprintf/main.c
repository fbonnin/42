#include "stdio.h"
#include "libft.h"
#include "locale.h"
int main()
{
	setlocale(LC_CTYPE, "en_US.UTF-8");
	printf("\nft returned : %d\n", ft_printf("% %"));
	printf("\nstd returned : %d\n", printf("% %"));
	return (0);
}
