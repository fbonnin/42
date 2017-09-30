#include "ls.h"

int		get_nb_elems(char *name, int *nb_blocks, int _a)
{
	int				result;
	DIR				*dir;
	struct dirent	*dirent;
	struct stat		info;

	result = 0;
	*nb_blocks = 0;
	dir = opendir(name);
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (dirent->d_name[0] != '.' || _a)
		{
			result++;
			stat(dirent->d_name, &info);
			*nb_blocks += info.st_blocks / 2;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (result);
}

char	**get_elems(char *name, int nb_elems, int _a)
{
	char			**elems;
	int				i;
	DIR				*dir;
	struct dirent	*dirent;

	elems = malloc(nb_elems * sizeof(char *));
	i = 0;
	dir = opendir(name);
	dirent = readdir(dir);
	while (dirent != NULL && i < nb_elems)
	{
		if (dirent->d_name[0] != '.' || _a)
		{
			elems[i] = strjoin3(name, "/", dirent->d_name);
			i++;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (elems);
}

char	*strjoin3(char *s1, char *s2, char *s3)
{
	char *result;

	result = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	ft_strcpy(result, s1);
	ft_strcpy(result + ft_strlen(s1), s2);
	ft_strcpy(result + ft_strlen(s1) + ft_strlen(s2), s3);
	return (result);
}
