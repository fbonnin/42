#include "ls.h"

void ls_names(char **names, int nb_names, t_options options)
{
	int first;

	first = 1;
	ls_files(names, nb_names, options, &first);
	ls_dirs(names, nb_names, options, first);	
}

void ls_files(char **names, int nb_names, t_options options, int *first)
{
	int			i;
	struct stat	info;

	i = 0;
	while (i < nb_names)
	{
		stat(names[i], &info);
		if (!S_ISDIR(info.st_mode))
		{
			print_file(names[i], options.l);
			*first = 0;
		}
		i++;
	}
}

void ls_dirs(char **names, int nb_names, t_options options, int first)
{
	int			i;
	struct stat	info;

	i = 0;
	while (i < nb_names)
	{
		stat(names[i], &info);
		if (S_ISDIR(info.st_mode))
		{
			if (!first)
				ft_printf(1, "\n");
			if (nb_names > 1 && !options.R)
				ft_printf(1, "%s:\n", names[i]);
			ls_dir(names[i], options);
			first = 0;
		}
		i++;
	}
}

void ls_dir(char *name, t_options options)
{
	DIR		*dir;
	char	**elems;
	int		nb_elems;

	dir = opendir(name);
	if (dir == NULL)
	{
		ft_printf(1, "ls: %s: Permission denied\n", name);
		return ;
	}
	closedir(dir);
	if (options.R)
		ft_printf(1, "%s:\n", name);
	nb_elems = get_nb_elems(name, options.a);
	elems = get_elems(name, nb_elems, options.a);
	sort_elems(elems, nb_elems, options.t, options.r);
	if (options.l)
		ft_printf(1, "total %d\n", get_nb_blocks(elems, nb_elems));
	print_elems(elems, nb_elems, options.l);
	if (options.R)
		ls_subdirs(options, elems, nb_elems);
	free_elems(elems, nb_elems);
}

void free_elems(char **elems, int nb_elems)
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

void ls_subdirs(t_options options, char **elems, int nb_elems)
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
		stat(elems[i], &info);
		if (S_ISDIR(info.st_mode) &&
		!ft_strequ(elems[i] + j, ".") && !ft_strequ(elems[i] + j, ".."))
		{
			ft_printf(1, "\n");
			ls_dir(elems[i], options);
		}
		i++;
	}
}
