/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:56:15 by fbonnin           #+#    #+#             */
/*   Updated: 2017/07/23 15:43:06 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

typedef struct	s_move
{
	int ant;
	int destination;
	int time;
}				t_move;

typedef struct	s_list_move
{
	t_move				move;
	struct s_list_move	*next;
}				t_list_move;

typedef struct	s_list_moves
{
	t_list_move	*first;
	t_list_move	*last;
	int			nb_moves;
}				t_list_moves;

#endif
