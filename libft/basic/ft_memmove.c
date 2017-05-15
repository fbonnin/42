/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:31:22 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/15 13:54:31 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_memmove1(char *dst, const char *src, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	ft_memmove2(char *dst, const char *src, size_t n)
{
	long long i;

	i = n - 1;
	while (i >= 0)
	{
		dst[i] = src[i];
		i--;
	}
}

void		*ft_memmove(void *destination, const void *source, size_t n)
{
	char		*dst;
	const char	*src;

	dst = destination;
	src = source;
	if (destination < source)
		ft_memmove1(dst, src, n);
	else
		ft_memmove2(dst, src, n);
	return (destination);
}
