#include "ls.h"

int				get_nb_dirents(char *name, int _a)
{
	int				result;
	DIR				*dir;
	struct dirent	*dirent;

	result = 0;
	dir = opendir(name);
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (dirent->d_name[0] != '.' || _a)
			result++;
		dirent = readdir(dir);
	}
	closedir(dir);
	return (result);
}

struct dirent	**get_dirents(char *name, int nb_dirents, int _a)
{
	struct dirent	**dirents;
	int				i;
	DIR				*dir;
	struct dirent	*dirent;

	dirents = malloc(nb_dirents * sizeof(struct dirent *));
	i = 0;
	dir = opendir(name);
	dirent = readdir(dir);
	while (dirent != NULL && i < nb_dirents)
	{
		if (dirent->d_name[0] != '.' || _a)
		{
			dirents[i] = dirent;
			i++;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (dirents);
}
