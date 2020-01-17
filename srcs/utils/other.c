/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/17 14:06:19 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	sq_dist(t_vector origin, t_vector point)
{
	return (pow(point.x - origin.x, 2) + pow(point.y - origin.y, 2));
}

int		ft_scale(t_vector y_vec, t_vector n_vec, float y)
{
	float	k;
	float	c;

	k = (float)(n_vec.y - n_vec.x) / (y_vec.y - y_vec.x);
	c = (float)n_vec.x - (float)k * y_vec.x;
	return ((k * y + c));
}

int		convert_rgb(int r, int g, int b, float k)
{
	r *= k;
	g *= k;
	b *= k;
	r = (r > 255 ? 255 : r);
	g = (g > 255 ? 255 : g);
	b = (b > 255 ? 255 : b);
	r = (r < 0 ? 0 : r);
	g = (g < 0 ? 0 : g);
	b = (b < 0 ? 0 : b);
	return (0x010000 * r + 0x000100 * g + b);
}
