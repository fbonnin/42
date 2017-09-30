int get_max(char **table, int nb_rows, int i_col)
{
	int result;
	int i_row;

	result = 0;
	i_row = 0;
	while (i_row < nb_rows)
	{
		result = ft_max(result, ft_strlen(table[i_row][i_col]));
		i_row++;
	}
	return (result);
}
