/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:47:15 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 17:55:46 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_arg(char *arg)
{
	int			len_arg;
	int			i;
	long long	number;

	len_arg = ft_strlen(arg);
	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i = 1;
	if (len_arg - i == 0 || len_arg - i > 10)
		return (PS_ERROR);
	while (arg[i] != 0)
		if (!ft_isdigit(arg[i++]))
			return (PS_ERROR);
	number = ft_str_to_llint(arg);
	if (number < -2147483648 || number > 2147483647)
		return (PS_ERROR);
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int i;

	if (argc < 2)
		return (PS_ERROR);
	i = 1;
	while (i < argc)
		if (check_arg(argv[i++]) == PS_ERROR)
			return (PS_ERROR);
	return (0);
}

int			get_numbers(int argc, char **argv, t_push_swap *s)
{
	int i;

	if (check_args(argc, argv) == PS_ERROR)
		return (PS_ERROR);
	s->numbers = malloc((argc - 1) * sizeof(int));
	if (s->numbers == NULL)
		return (PS_ERROR);
	i = 0;
	while (i < argc - 1)
	{
		s->numbers[i] = ft_atoi(argv[1 + i]);
		i++;
	}
	s->nb_numbers = argc - 1;
	return (0);
}

static void	sort_numbers(t_push_swap *s, int *numbers)
{
	int i1;
	int i2;
	int t;

	i1 = 1;
	while (i1 < s->nb_numbers)
	{
		i2 = i1;
		while (i2 > 0 && numbers[i2 - 1] > numbers[i2])
		{
			t = numbers[i2 - 1];
			numbers[i2 - 1] = numbers[i2];
			numbers[i2] = t;
			i2--;
		}
		i1++;
	}
}

int			check_duplicates(t_push_swap *s)
{
	int *copy;
	int i;

	copy = malloc(s->nb_numbers * sizeof(int));
	if (copy == NULL)
		return (PS_ERROR);
	i = 0;
	while (i < s->nb_numbers)
	{
		copy[i] = s->numbers[i];
		i++;
	}
	sort_numbers(s, copy);
	i = 0;
	while (i < s->nb_numbers - 1)
	{
		if (copy[i] == copy[i + 1])
		{
			free(copy);
			return (PS_ERROR);
		}
		i++;
	}
	free(copy);
	return (0);
}
