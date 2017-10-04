#include "ls.h"

char	**get_files(char **params, int nb_params, int *nb_files)
{
	char		**files;
	int			i_file;
	int			i;
	struct stat	info;

	*nb_files = 0;
	i = 0;
	while (i < nb_params)
	{
		if (lstat(params[i++], &info) == 0 && !S_ISDIR(info.st_mode))
			(*nb_files)++;
	}
	files = malloc(*nb_files * sizeof(char *));
	i_file = 0;
	i = 0;
	while (i < nb_params && i_file < *nb_files)
	{
		if (lstat(params[i], &info) == 0 && !S_ISDIR(info.st_mode))
			files[i_file++] = params[i];
		i++;
	}
	return (files);
}

char	**get_dirs(char **params, int nb_params, int *nb_dirs)
{
	char		**dirs;
	int			i_dir;
	int			i;
	struct stat	info;

	*nb_dirs = 0;
	i = 0;
	while (i < nb_params)
	{
		if (lstat(params[i++], &info) == 0 && S_ISDIR(info.st_mode))
			(*nb_dirs)++;
	}
	dirs = malloc(*nb_dirs * sizeof(char *));
	i_dir = 0;
	i = 0;
	while (i < nb_params && i_dir < *nb_dirs)
	{
		if (lstat(params[i], &info) == 0 && S_ISDIR(info.st_mode))
			dirs[i_dir++] = params[i];
		i++;
	}
	return (dirs);
}

int		get_nb_elems(char *dir_name, int _a)
{
	int				result;
	DIR				*dir;
	struct dirent	*dirent;

	result = 0;
	dir = opendir(dir_name);
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

char	**get_elems(char *dir_name, int nb_elems, int _a)
{
	char			**elems;
	int				i;
	DIR				*dir;
	struct dirent	*dirent;

	elems = malloc(nb_elems * sizeof(char *));
	i = 0;
	dir = opendir(dir_name);
	dirent = readdir(dir);
	while (dirent != NULL && i < nb_elems)
	{
		if (dirent->d_name[0] != '.' || _a)
		{
			elems[i] = strjoin3(dir_name, "/", dirent->d_name);
			i++;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (elems);
}

void	free_elems(char **elems, int nb_elems)
{
	int i;

	i = 0;
	while (i < nb_elems)
	{
		free(elems[i]);
		i++;
	}
	free(elems);
}
