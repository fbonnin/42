/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:45:47 by fbonnin           #+#    #+#             */
/*   Updated: 2017/06/07 16:54:19 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	free_everything(int *numbers, t_list *a, t_list *b)
{
	free(numbers);
	free_list(a);
	free_list(b);
	return (CHECK_ERROR);
}

static int	check(int argc, char **argv)
{
	int		*numbers;
	t_list	a;
	t_list	b;
	char	*line;
	int		r;

	if (get_numbers(argc, argv, &numbers) == CHECK_ERROR)
		return (CHECK_ERROR);
	initialize_list(&a);
	initialize_list(&b);
	if (check_duplicates(numbers, argc - 1) == CHECK_ERROR)
		return (free_everything(numbers, &a, &b));
	if (numbers_to_a(numbers, argc - 1, &a) == CHECK_ERROR)
		return (free_everything(numbers, &a, &b));
	while ((r = ft_get_next_line(0, &line)) == 1)
	{
		if (do_operations(&a, &b, line) == CHECK_ERROR)
			return (free_everything(numbers, &a, &b));
		free(line);
	}
	if (r == -1)
		return (free_everything(numbers, &a, &b));
	r = check_result(&a, &b);
	free_everything(numbers, &a, &b);
	return (r);
}

int			main(int argc, char **argv)
{
	int r;

	if (argc < 2)
		return (0);
	r = check(argc, argv);
	if (r == CHECK_ERROR)
		write(2, "Error\n", 6);
	else if (r == 1)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (0);
}
