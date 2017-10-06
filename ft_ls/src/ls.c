/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:53:52 by fbonnin           #+#    #+#             */
/*   Updated: 2017/10/06 16:02:26 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls_params(char **params, int nb_params, t_options options)
{
	char	**elems;
	int		nb_elems;
	int		i;
	int		first;

	print_non_existent(params, nb_params);
	if ((elems = get_files(params, nb_params, &nb_elems)) != NULL)
		print_elems(elems, nb_elems, options);
	free(elems);
	first = (nb_elems == 0);
	if ((elems = get_dirs(params, nb_params, &nb_elems)) == NULL)
		return ;
	sort_elems(elems, nb_elems, options.t, options.r);
	i = 0;
	while (i < nb_elems)
	{
		if (!first)
			ft_printf(1, "\n");
		first = 0;
		if (nb_params > 1 && !options.rr)
			ft_printf(1, "%s:\n", elems[i]);
		ls_dir(elems[i++], options);
	}
	free(elems);
}

void	print_non_existent(char **params, int nb_params)
{
	int			i;
	struct stat	info;

	i = 0;
	while (i < nb_params)
	{
		if (lstat(params[i], &info) == -1)
			ft_printf(1, "ls: %s: No such file or directory\n", params[i]);
		i++;
	}
}

void	ls_dir(char *dir_name, t_options options)
{
	DIR		*dir;
	char	**elems;
	int		nb_elems;

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		ft_printf(1, "ls: %s: Permission denied\n", dir_name);
		return ;
	}
	closedir(dir);
	if (options.rr)
		ft_printf(1, "%s:\n", dir_name);
	nb_elems = get_nb_elems(dir_name, options.a);
	elems = get_elems(dir_name, nb_elems, options.a);
	if (options.l)
		ft_printf(1, "total %d\n", get_nb_blocks(elems, nb_elems));
	print_elems(elems, nb_elems, options);
	if (options.rr)
		ls_subdirs(options, elems, nb_elems);
	free_elems(elems, nb_elems);
}

void	ls_subdirs(t_options options, char **elems, int nb_elems)
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
		lstat(elems[i], &info);
		if (S_ISDIR(info.st_mode) &&
		!ft_strequ(elems[i] + j, ".") && !ft_strequ(elems[i] + j, ".."))
		{
			ft_printf(1, "\n");
			ls_dir(elems[i], options);
		}
		i++;
	}
}
