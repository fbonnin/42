#include "../libft.h"

int	ft_size_wchar(wchar_t c)
{
	if (c < 128)
		return (1);
	if (c < 2048)
		return (2);
	if (c < 65536)
		return (3);
	return (4);
}
