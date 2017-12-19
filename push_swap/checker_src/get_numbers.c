/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:38:28 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 16:48:38 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
		return (CHECK_ERROR);
	while (arg[i] != 0)
		if (!ft_isdigit(arg[i++]))
			return (CHECK_ERROR);
	number = ft_str_to_llint(arg);
	if (number < -2147483648 || number > 2147483647)
		return (CHECK_ERROR);
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int i;

	if (argc < 2)
		return (CHECK_ERROR);
	i = 1;
	while (i < argc)
		if (check_arg(argv[i++]) == CHECK_ERROR)
			return (CHECK_ERROR);
	return (0);
}

int			get_numbers(int argc, char **argv, int **numbers)
{
	int i;

	if (check_args(argc, argv) == CHECK_ERROR)
		return (CHECK_ERROR);
	*numbers = malloc((argc - 1) * sizeof(int));
	if (*numbers == NULL)
		return (CHECK_ERROR);
	i = 0;
	while (i < argc - 1)
	{
		(*numbers)[i] = ft_atoi(argv[1 + i]);
		i++;
	}
	return (0);
}

static void	sort_numbers(int *numbers, int nb_numbers)
{
	int i1;
	int i2;
	int t;

	i1 = 1;
	while (i1 < nb_numbers)
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

int			check_duplicates(int *numbers, int nb_numbers)
{
	int *copy;
	int i;

	copy = malloc(nb_numbers * sizeof(int));
	if (copy == NULL)
		return (CHECK_ERROR);
	i = 0;
	while (i < nb_numbers)
	{
		copy[i] = numbers[i];
		i++;
	}
	sort_numbers(copy, nb_numbers);
	i = 0;
	while (i < nb_numbers - 1)
	{
		if (copy[i] == copy[i + 1])
		{
			free(copy);
			return (CHECK_ERROR);
		}
		i++;
	}
	free(copy);
	return (0);
}
