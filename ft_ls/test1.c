#include <stdio.h>
#include <dirent.h>

int main(int ac, char **av)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(av[1]);
	entry = readdir(dir);
	while (entry != NULL)
	{
		printf("%s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}
