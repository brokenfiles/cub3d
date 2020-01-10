/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/10 20:10:15 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_vector	rotation_matrice(t_vector point, t_vector origin, float teta)
{
	t_vector	vector;
	float		alpha;
	float		c;
	float		s;

	alpha = (teta / 360.0) * (float)(2 * M_PI);
	c = -cos(alpha);
	s = -sin(alpha);
	vector.x = (point.x - origin.x) * c +
			   (point.y - origin.y) * s + origin.x;
	vector.y = -(point.x - origin.x) * s +
			   (point.y - origin.y) * c + origin.y;
	return (vector);
}

