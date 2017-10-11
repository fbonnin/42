/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:54:09 by fbonnin           #+#    #+#             */
/*   Updated: 2017/10/06 16:01:00 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		main(int ac, char **av)
{
	char		**params;
	int			nb_params;
	t_options	options;
	int			i;
	char		dot[2];

	if (init_ls(ac, &params, &nb_params, &options) == -1)
		return (0);
	i = 1;
	while (i < ac)
	{
		if (parse_av(params, &nb_params, &options, av[i]) == -1)
			return (end_ls(params));
		i++;
	}
	dot[0] = '.';
	dot[1] = 0;
	if (nb_params == 0)
	{
		params[0] = dot;
		nb_params = 1;
	}
	ls_params(params, nb_params, options);
	return (end_ls(params));
}

int		init_ls(int ac, char ***params, int *nb_params, t_options *options)
{
	if ((*params = malloc(ft_max(ac, 1) * sizeof(char *))) == NULL)
		return (-1);
	*nb_params = 0;
	options->a = 0;
	options->l = 0;
	options->r = 0;
	options->rr = 0;
	options->t = 0;
	return (0);
}

int		parse_av(char **params, int *nb_params, t_options *options, char *av)
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
		params[(*nb_params)++] = av;
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
		options->rr = 1;
	else if (option == 't')
		options->t = 1;
	else
	{
		ft_printf(1, "ls: invalid option -- '%c'\n", option);
		return (-1);
	}
	return (0);
}

int		end_ls(char **params)
{
	free(params);
	return (0);
}
