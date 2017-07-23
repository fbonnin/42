/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:56:44 by fbonnin           #+#    #+#             */
/*   Updated: 2017/07/23 15:42:09 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

typedef struct	s_neighbor
{
	int					i_node;
	struct s_neighbor	*next;
}				t_neighbor;

typedef struct	s_node
{
	char		*name;
	t_neighbor	*neighbors;
	int			time_available;
	int			reached;
	int			time_reach;
	int			previous;
}				t_node;

#endif
