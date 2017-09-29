int main(int ac, char **av)
{
	char		**names;
	int			nb_names;
	t_options	options;
	int			i;
	char		dot[2];

	init_ls(&names, &nb_names, &options);
	i = 1;
	while (i < ac)
	{
		parse_av(names, &nb_names, &options, av[i]);
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
	return (0);
}

void	init_ls(char ***names, int *nb_names, t_options *options)
{
	*names = malloc(ac * sizeof(char *));
	*nb_names = 0;
	options->a = 0;
	options->l = 0;
	options->r = 0;
	options->R = 0;
	options->t = 0;
}

void	parse_av(char **names, int *nb_names, t_options *options, char *av)
{
	int i;

	if (a[0] == '-')
	{
		i = 1;
		while (av[i] != 0)
		{
			if (av[i] == 'a')
				options.a = 1;
			else if (av[i] == 'l')
				options.l = 1;
			else if (av[i] == 'r')
				options.r = 1;
			else if (av[i] == 'R')
				options.R = 1;
			else if (av[i] == 't')
				options.t = 1;
			else
				ft_printf("ls: invalid option -- '%c'\n", av[i]);
			j++;
		}
	}
	else
		names[nb_names++] = av;
}
