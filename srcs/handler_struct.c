/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:24:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/03 16:34:35 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_player(t_player *player)
{
	player->rotation_speed = 7;
	player->speed = 0.5;
	player->health = 100;
	player->size = 1;
	return (1);
}

t_dimension	*init_dimension(int width, int height)
{
	t_dimension	*dimension;

	if (!(dimension = malloc(sizeof(t_dimension))))
		return (NULL);
	dimension->height = height;
	dimension->width = width;
	return (dimension);
}

t_vector	*init_vector(int x, int y)
{
	t_vector	*vector;

	if (!(vector = malloc(sizeof(t_vector))))
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_location	*init_location(float x, float y, float yaw)
{
	t_location	*location;

	if (!(location = malloc(sizeof(t_location))))
		return (NULL);
	location->x = x;
	location->y = y;
	location->yaw = yaw;
	return (location);
}

t_rectangle	*init_rectangle(t_dimension *dimension, t_vector *vector, int color)
{
	t_rectangle	*rectangle;

	if (!(rectangle = malloc(sizeof(t_rectangle))))
		return (NULL);
	rectangle->dimension = dimension;
	rectangle->vector = vector;
	rectangle->color = color;
	return (rectangle);
}

t_triangle	*init_triangle(t_vector *vector1, t_vector *vector2, int color)
{
	t_triangle	*triangle;

	if (!(triangle = malloc(sizeof(t_triangle))))
		return (NULL);
	triangle->vector1 = vector1;
	triangle->vector2 = vector2;
	triangle->color = color;
	return (triangle);
}


t_tri    *init_tri(t_vector *vector, int height, int color)
{
    t_tri    *triangle;
    
    if (!(triangle = malloc(sizeof(t_tri))))
        return (NULL);
    triangle->vector = vector;
    triangle->height = height;
    triangle->color = color;
    return (triangle);
}
