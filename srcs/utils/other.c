/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 18:16:10 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float		sq_dist(t_vector origin, t_vector point)
{
	return (pow(point.x - origin.x, 2) + pow(point.y - origin.y, 2));
}

int ft_scale(int ymin, int ymax, int nmin, int nmax, float y)
{
	float k;
	float c;

	k = (float) (nmax - nmin) / (ymax - ymin);
	c = (float) nmin - (float) k * ymin;
	return ((k * y + c));
}

int convert_rgb(int R, int G, int B)
{
	R = (R > 255 ? 255 : R);
	G = (G > 255 ? 255 : G);
	B = (B > 255 ? 255 : B);
	R = (R < 0 ? 0 : R);
	G = (G < 0 ? 0 : G);
	B = (B < 0 ? 0 : B);
	return (65536 * R + 256 * G + B);
}