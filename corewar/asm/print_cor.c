#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/types.h"

int	main()
{
	int i = 0;
	int fd;
	unsigned char c;

	fd = open("example.cor", O_RDONLY);
	while (read(fd, &c, 1) != 0)
	{
		i++;
		printf("%d ", c);
		if (i % 10 == 0)
			printf("\n");
		if (i % 100 == 0)
			printf("\n\n");
	}
	printf("\n%d\n", i);
	return (0);
}
