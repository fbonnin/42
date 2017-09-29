void ls_dir(char *name, t_options options)
{
	DIR				*dir;
	struct dirent	**dirents;
	int				nb_dirents;

	dir = opendir(name);
	if (options.R)
		ft_printf("%s:\n", name);
	nb_dirents = get_nb_dirents(dir, options.a);
	dirents = get_dirents(dir, nb_dirents, options.a);
	sort_dirents(dirents, nb_dirents, options.t, options.r);
	if (options.l)
		ft_printf("total %d\n", nb_dirents);
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
			ft_printf("\n\n");
			ls_dir(subdir, options);
			free(subdir);
		}
		i++;
	}
}
