/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splited_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:57:36 by acorbeau          #+#    #+#             */
/*   Updated: 2017/04/26 18:19:24 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fillit.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"

static int		read_buffer(char *path, char **buffer)
{
	int	fd;
	int	readed;

	readed = -1;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (-1);
	if ((*buffer = ft_strnew(BUFFER_SIZE)) == NULL)
		return (-1);
	if ((readed = read(fd, *buffer, BUFFER_SIZE)) < 19)
	{
		free(*buffer);
		return (-1);
	}
	close(fd);
	return (readed);
}

static int		free_memory(char **buffer, char ***tetris, int index)
{
	if (*buffer)
		free(*buffer - ((index - 1) * 21));
	if (tetris)
		free(*tetris - (index - 1));
	*buffer = NULL;
	*tetris = NULL;
	return (-1);
}

static int		split_buff(char *buffer, char **tetris, int tetri_count)
{
	int index;

	index = 0;
	while (index++ < tetri_count)
	{
		if ((*tetris = ft_strnew(20)) == NULL)
			return (free_memory(&buffer, &tetris, index));
		if (!tetri_match_rules(buffer))
			return (free_memory(&buffer, &tetris, index));
		ft_memcpy(*tetris, buffer, 20);
		if (!tetri_is_valide(*tetris))
			return (free_memory(&buffer, &tetris, index));
		if (index < tetri_count)
		{
			buffer += 21;
			tetris++;
		}
		else if (buffer[20] == '\n')
			return (free_memory(&buffer, &tetris, index));
	}
	free(buffer - ((tetri_count - 1) * 21));
	return (1);
}

int				get_splited_file(char *path, char ***ts)
{
	char	*buffer;
	int		index;
	int		readed;
	int		tetri_count;
	char	**tetris;

	index = 0;
	tetri_count = 1;
	if ((readed = read_buffer(path, &buffer)) == -1)
		return (-1);
	while ((tetri_count * 20) + tetri_count + 1 <= readed)
		tetri_count++;
	if (!(tetris = (char **)ft_memalloc((sizeof(char *) * tetri_count))) &&
(readed - ((tetri_count * 21) - 1)) != 0)
	{
		free(buffer);
		return (-1);
	}
	if (split_buff(buffer, tetris, tetri_count) != 1)
		return (-1);
	*ts = tetris;
	return (tetri_count);
}
