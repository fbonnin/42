#include <stdio.h>
#include <dirent.h>

int main(int ac, char **av)
{
	DIR *dir;
	struct dirent *dirent;

	dir = opendir(av[1]);
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		printf("%s\n", dirent->d_name);
		dirent = readdir(dir);
	}
	closedir(dir);
	return (0);
}
