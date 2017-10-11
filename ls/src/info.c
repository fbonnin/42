/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 15:53:47 by fbonnin           #+#    #+#             */
/*   Updated: 2017/10/06 15:57:05 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	get_type(struct stat info)
{
	int m;

	m = info.st_mode;
	if (S_ISREG(m))
		return ('-');
	if (S_ISBLK(m))
		return ('b');
	if (S_ISCHR(m))
		return ('c');
	if (S_ISDIR(m))
		return ('d');
	if (S_ISLNK(m))
		return ('l');
	if (S_ISFIFO(m))
		return ('p');
	if (S_ISSOCK(m))
		return ('s');
	return ('E');
}

void	get_rights(struct stat info, char *rights)
{
	int m;

	m = info.st_mode;
	rights[0] = m & S_IRUSR ? 'r' : '-';
	rights[1] = m & S_IWUSR ? 'w' : '-';
	rights[2] = m & S_IXUSR ? 'x' : '-';
	rights[3] = m & S_IRGRP ? 'r' : '-';
	rights[4] = m & S_IWGRP ? 'w' : '-';
	rights[5] = m & S_IXGRP ? 'x' : '-';
	rights[6] = m & S_IROTH ? 'r' : '-';
	rights[7] = m & S_IWOTH ? 'w' : '-';
	rights[8] = m & S_IXOTH ? 'x' : '-';
}
