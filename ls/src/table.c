/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:53:25 by fbonnin           #+#    #+#             */
/*   Updated: 2017/10/06 15:53:26 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		fill_table(char **elems, int nb_elems, char ***table)
{
	int			i;
	struct stat	info;

	i = 0;
	while (i < nb_elems)
	{
		if (lstat(elems[i], &info) == -1)
			return (-1);
		if (get_row_1(info, table[i]) == -1)
			return (-1);
		if (get_row_2(info, table[i]) == -1)
			return (-1);
		if (get_row_3(elems[i], table[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int		get_width(char ***table, int nb_rows, int i_col)
{
	int result;
	int i_row;

	result = 0;
	i_row = 0;
	while (i_row < nb_rows)
	{
		if (table[i_row][i_col] != NULL)
			result = ft_max(result, ft_strlen(table[i_row][i_col]));
		i_row++;
	}
	return (result);
}

void	print_table(char ***table, int nb_rows, int *widths)
{
	int		i;
	char	**row;
	int		width456;

	i = 0;
	while (i < nb_rows)
	{
		row = table[i];
		ft_printf(1, "%s ", row[0]);
		ft_printf(1, "%*s ", widths[1], row[1]);
		ft_printf(1, "%-*s ", widths[2], row[2]);
		ft_printf(1, "%-*s ", widths[3], row[3]);
		width456 = ft_max(widths[4], widths[5] + 1 + 1 + widths[6]);
		if (row[0][0] == 'b' || row[0][0] == 'c')
		{
			ft_printf(1, "%*s, ", width456 - 1 - 1 - widths[6], row[5]);
			ft_printf(1, "%*s ", widths[6], row[6]);
		}
		else
			ft_printf(1, "%*s ", width456, row[4]);
		ft_printf(1, "%s ", row[7] + 4);
		ft_printf(1, "%s\n", row[8]);
		i++;
	}
}
