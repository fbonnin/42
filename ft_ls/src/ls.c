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
	DIR				*dir;
	struct dirent	**dirents;
	int				nb_dirents;

	dir = opendir(name);
	if (options.R)
		ft_printf(1, "%s:\n", name);
	nb_dirents = get_nb_dirents(dir, options.a);
	dirents = get_dirents(dir, nb_dirents, options.a);
	sort_dirents(dirents, nb_dirents, options.t, options.r);
	if (options.l)
		ft_printf(1, "total %d\n", nb_dirents);
	print_dirents(dirents, nb_dirents, options.l);
	if (options.R)
		ls_subdirs(name, options, dirents, nb_dirents);
	free(dirents);
}

void ls_subdirs(char *name, t_options options,
struct dirent **dirents, int nb_dirents)
{
	int			i;
	struct stat	info;
	char		*subdir;

	i = 0;
	while (i < nb_dirents)
	{
		stat(dirents[i]->d_name, &info);
		if (S_ISDIR(info.st_mode))
		{
			subdir = ft_strnew(ft_strlen(name) +
			1 + ft_strlen(dirents[i]->d_name));
			ft_strcpy(subdir, name);
			subdir[ft_strlen(name)] = '/';
			ft_strcpy(subdir + ft_strlen(name) + 1, dirents[i]->d_name);
			ft_printf(1, "\n");
			ls_dir(subdir, options);
			free(subdir);
		}
		i++;
	}
}
