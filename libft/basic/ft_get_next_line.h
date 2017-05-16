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

# define GNL_BUFF_SIZE 1000
# define GNL_MAX_NB_FILES 100
# define GNL_MAX_LINE_SIZE 100000

typedef struct	s_s
{
	char	buff[GNL_MAX_NB_FILES][GNL_BUFF_SIZE];
	int		nb_bytes_read[GNL_MAX_NB_FILES];
	int		i_byte[GNL_MAX_NB_FILES];
	int		files[GNL_MAX_NB_FILES];
	int		nb_files;
	char	line[GNL_MAX_LINE_SIZE];
	int		line_size;
}				t_s;

int				get_next_line(const int fd, char **line);

#endif
