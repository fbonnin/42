char	***alloc_table(int nb_rows)
{
	char	***table;
	int		i;
	int		j;

	if ((table = malloc(nb_rows * sizeof(char **))) == NULL)
		return (NULL);
	i = 0;
	while (i < nb_rows)
	{
		if ((table[i] = malloc(9 * sizeof(char *))) == NULL)
		{
			while (--i >= 0)
				free(table[i]);
			free(table);
			return (NULL);
		}
		j = 0;
		while (j < 9)
			table[i][j++] = NULL;
		i++;
	}
	return (table);
}

void	free_table(char ***table, int nb_rows)
{
	int i;
	int j;

	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (j < 9)
		{
			free(table[i][j]);
			j++;
		}
		free(table[i]);
		i++;
	}
	free(table);
}
