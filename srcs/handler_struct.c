/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:24:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 13:05:46 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_player(t_player *player)
{
	player->rot_speed = 7;
	player->speed = 0.5;
	player->health = 100;
	player->size = 1;
	return (1);
}

t_vector	*init_vector(float x, float y)
{
	t_vector	*vector;

	if (!(vector = malloc(sizeof(t_vector))))
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_form	*init_form(t_vector *vector, t_vector *dim, int color)
{
	t_form	*form;

	if (!(form = malloc(sizeof(t_form))))
		return (NULL);
	form->dim = dim;
	form->vector = vector;
	form->color = color;
	return (form);
}
