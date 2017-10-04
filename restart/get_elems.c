#include "ls.h"

char	**get_files(char **elems, int nb_elems, int *nb_files)
{
	char		**files;
	int			i_file;
	int			i;
	struct stat	info;

	*nb_files = 0;
	i = 0;
	while (i < nb_elems)
	{
		if (lstat(elems[i++], &info) == 0 && !S_ISDIR(info.st_mode))
			(*nb_files)++;
	}
	files = malloc(*nb_files * sizeof(char *));
	i_file = 0;
	i = 0;
	while (i < nb_elems && i_file < *nb_files)
	{
		lstat(elems[i], &info);
		if (!S_ISDIR(info.st_mode))
			files[i_file++] = elems[i];
		i++;
	}
	return (files);
}

char	**get_dirs(char **elems, int nb_elems, int *nb_dirs)
{
	char		**dirs;
	int			i_dir;
	int			i;
	struct stat	info;

	*nb_dirs = 0;
	i = 0;
	while (i < nb_elems)
	{
		if (lstat(elems[i++], &info) == 0 && S_ISDIR(info.st_mode))
			(*nb_dirs)++;
	}
	dirs = malloc(*nb_dirs * sizeof(char *));
	i_dir = 0;
	i = 0;
	while (i < nb_elems && i_dir < *nb_dirs)
	{
		lstat(elems[i], &info);
		if (S_ISDIR(info.st_mode))
			dirs[i_dir++] = elems[i];
		i++;
	}
	return (dirs);
}

int		get_nb_elems(char *name, int _a)
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

int		get_nb_blocks(char **elems, int nb_elems)
{
	int			result;
	int			i;
	struct stat	info;

	result = 0;
	i = 0;
	while (i < nb_elems)
	{
		lstat(elems[i], &info);
		result += info.st_blocks / 2;
		i++;
	}
	return (result);
}
