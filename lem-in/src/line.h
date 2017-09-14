/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:55:57 by fbonnin           #+#    #+#             */
/*   Updated: 2017/07/23 15:39:45 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

typedef struct	s_line
{
	char			*str;
	struct s_line	*next;
}				t_line;

typedef struct	s_lines
{
	t_line *first;
	t_line *last;
}				t_lines;

#endif
