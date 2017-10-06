/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_row.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:53:42 by fbonnin           #+#    #+#             */
/*   Updated: 2017/10/06 15:59:01 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	get_row_1(struct stat info, char **row)
{
	struct passwd	*usr;
	struct group	*grp;

	if ((row[0] = ft_strnew(10)) == NULL)
		return (-1);
	row[0][0] = get_type(info);
	get_rights(info, row[0] + 1);
	if ((row[1] = ft_itoa(info.st_nlink)) == NULL)
		return (-1);
	if ((usr = getpwuid(info.st_uid)) == NULL)
		return (-1);
	if ((row[2] = ft_strdup(usr->pw_name)) == NULL)
		return (-1);
	if ((grp = getgrgid(info.st_gid)) == NULL)
		return (-1);
	if ((row[3] = ft_strdup(grp->gr_name)) == NULL)
		return (-1);
	return (0);
}

int	get_row_2(struct stat info, char **row)
{
	if (row[0][0] == 'b' || row[0][0] == 'c')
	{
		if ((row[5] = ft_itoa(major(info.st_rdev))) == NULL)
			return (-1);
		if ((row[6] = ft_itoa(minor(info.st_rdev))) == NULL)
			return (-1);
	}
	else if ((row[4] = ft_itoa(info.st_size)) == NULL)
		return (-1);
	if ((row[7] = ft_strdup(ctime(&info.st_mtime))) == NULL)
		return (-1);
	row[7][16] = 0;
	return (0);
}

int	get_row_3(char *elem, char **row)
{
	int		i_name;
	char	link_contents[101];
	int		i;

	i_name = ft_strlen(elem);
	while (i_name > 0 && elem[i_name - 1] != '/')
		i_name--;
	if (row[0][0] == 'l')
	{
		i = 0;
		while (i < 101)
			link_contents[i++] = 0;
		if (readlink(elem, link_contents, 100) == -1)
			return (-1);
		if ((row[8] = strjoin3(elem + i_name, " -> ", link_contents))
		== NULL)
			return (-1);
	}
	else if ((row[8] = ft_strdup(elem + i_name)) == NULL)
		return (-1);
	return (0);
}
