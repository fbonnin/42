#include "ls.h"

void	ls_params(char **params, int nb_params, t_options options)
{
	char	**elems;
	int		nb_elems;
	int		i;
	int		first;

	elems = get_files(params, nb_params, &nb_elems);
	print_elems(elems, nb_elems, options);
	free_elems(elems, nb_elems);
	first = (nb_elems > 0);
	elems = get_dirs(params, nb_params, &nb_elems);
	i = 0;
	while (i < nb_elems)
	{
		if (!first)
			ft_printf(1, "\n");
		first = 0;
		if (nb_params > 1 && !options.R)
			ft_printf(1, "%s:\n", elems[i]);
		ls_dir(elems[i++], options);
	}
	free_elems(elems, nb_elems);
}

void	ls_dir(char *dir_name, t_options options)
{
	DIR		*dir;
	char	**elems;
	int		nb_elems;

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		ft_printf(1, "ls: %s: Permission denied\n", dir_name);
		return ;
	}
	closedir(dir);
	if (options.R)
		ft_printf(1, "%s:\n", dir_name);
	nb_elems = get_nb_elems(dir_name, options.a);
	elems = get_elems(dir_name, nb_elems, options.a);
	if (options.l)
		ft_printf(1, "total %d\n", get_nb_blocks(elems, nb_elems));
	print_elems(elems, nb_elems, options);
	if (options.R)
		ls_subdirs(options, elems, nb_elems);
	free_elems(elems, nb_elems);
}

void	ls_subdirs(t_options options, char **elems, int nb_elems)
{
	int			i;
	int			j;
	struct stat	info;

	i = 0;
	while (i < nb_elems)
	{
		j = ft_strlen(elems[i]);
		while (j > 0 && elems[i][j - 1] != '/')
			j--;
		lstat(elems[i], &info);
		if (S_ISDIR(info.st_mode) &&
		!ft_strequ(elems[i] + j, ".") && !ft_strequ(elems[i] + j, ".."))
		{
			ft_printf(1, "\n");
			ls_dir(elems[i], options);
		}
		i++;
	}
}