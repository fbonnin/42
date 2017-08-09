#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int	main(int argc, char **argv)
{
	int				fd;
	unsigned char	byte;
	int				i;

	printf("\n\n\n");
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (read(fd, &byte, 1) != 0)
	{
		printf("%4d", byte);
		i++;
		if (i % 10 == 0)
			printf("\n");
		if (i % 100 == 0)
			printf("%4d\n\n", i / 100);
	}
	printf("\n\n\n");
	return (0);
}
