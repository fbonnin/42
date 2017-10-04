int	print_elems(char **elems, int nb_elems, t_options options)
{
	int i;
	int i_name;

	sort_elems(elems, nb_elems, options.t, options.r);
	if (options.l)
		print_elems_l(elems, nb_elems);
	else
	{
		i = 0;
		while (i < nb_elems)
		{
			i_name = ft_strlen(elems[i]);
			while (i_name > 0 && elems[i][i_name - 1] != '/')
				i_name--;
			ft_printf(1, "%s\n", elems[i] + i_name);
			i++;
		}
	}
}


int	print_elems_l(char **elems, int nb_elems)
{
	char	***table;
	int		widths[9];
	int		i;

	if ((table = alloc_table(nb_elems)) == NULL)
		return (-1);
	if (fill_table(elems, nb_elems, table) == -1)
	{
		free_table(table, nb_elems);
		return (-1);
	}
	i = 0;
	while (i < 9)
	{
		widths[i] = get_width(table, nb_elems, i);
		i++;
	}
	print_table(table, nb_elems, widths);
	return (0);
}
