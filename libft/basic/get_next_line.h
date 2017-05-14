/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:06:07 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/10 18:49:38 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1000
# define MAX_NB_FILES 100
# define MAX_LINE_SIZE 100000

typedef struct	s_s
{
	char	buff[MAX_NB_FILES][BUFF_SIZE];
	int		nb_bytes_read[MAX_NB_FILES];
	int		i_byte[MAX_NB_FILES];
	int		files[MAX_NB_FILES];
	int		nb_files;
	char	line[MAX_LINE_SIZE];
	int		line_size;
}				t_s;

int				get_next_line(const int fd, char **line);

#endif
