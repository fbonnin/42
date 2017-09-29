int		main(int ac, char **av)
{
	char		**names;
	int			nb_names;
	t_options	options;
	int			i;
	char		dot[2];

	init_ls(ac, &names, &nb_names, &options);
	i = 1;
	while (i < ac)
	{
		if (parse_av(names, &nb_names, &options, av[i]) == -1)
			return (end_ls(names));
		i++;
	}
	dot[0] = '.';
	dot[1] = 0;
	if (nb_names == 0)
	{
		names[0] = dot;
		nb_names = 1;
	}
	ls_names(names, nb_names, options);
	return (end_ls(names));
}

void	init_ls(int ac, char ***names, int *nb_names, t_options *options)
{
	*names = malloc(ft_max(ac, 1) * sizeof(char *));
	*nb_names = 0;
	options->a = 0;
	options->l = 0;
	options->r = 0;
	options->R = 0;
	options->t = 0;
}

int		parse_av(char **names, int *nb_names, t_options *options, char *av)
{
	int i;

	if (av[0] == '-')
	{
		i = 1;
		while (av[i] != 0)
		{
			if (parse_option(options, av[i]) == -1)
				return (-1);
			i++;
		}
	}
	else
		names[(*nb_names)++] = av;
	return (0);
}

int		parse_option(t_options *options, char option)
{
	if (option == 'a')
		options->a = 1;
	else if (option == 'l')
		options->l = 1;
	else if (option == 'r')
		options->r = 1;
	else if (option == 'R')
		options->R = 1;
	else if (option == 't')
		options->t = 1;
	else
	{
		ft_printf("ls: invalid option -- '%c'\n", option);
		return (-1);
	}
	return (0);
}

int		end_ls(char **names)
{
	free(names);
	return (0);
}
