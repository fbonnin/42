/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonnin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 13:31:23 by fbonnin           #+#    #+#             */
/*   Updated: 2017/05/18 17:04:48 by fbonnin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_xyz_double	normalize(t_xyz_double vector)
{
	double magnitude;

	magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	vector.x /= magnitude;
	vector.y /= magnitude;
	vector.z /= magnitude;
	return (vector);
}
