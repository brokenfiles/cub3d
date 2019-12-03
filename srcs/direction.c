/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:50:31 by llaurent          #+#    #+#             */
/*   Updated: 2019/11/28 19:03:51 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int direction_change(t_player *player, float inc)
{
	player->location.yaw += inc;
	if (player->location.yaw > 360 || player->location.yaw <= 0)
		player->location.yaw = player->location.yaw > 0 ? player->location.yaw % 360 : 360;
	return (1);
}

t_vector *rotation_matrice(t_player *player, int x, int y)
{
	t_vector *vector;

	if (!(vector = malloc(sizeof(t_vector))))
		return (NULL);
	vector->x = (x - 15 * player->location.x) * cos((player->location.yaw / 360.0) * (float) (2 * M_PI)) +
				(y - 15 * player->location.y) * sin((player->location.yaw / 360.0) * (float) (2 * M_PI)) +
			15 * player->location.x;
	vector->y = -(x - 15 * player->location.x) * sin((player->location.yaw / 360.0) * (float) (2 * M_PI)) +
				(y - 15 * player->location.y) * cos((player->location.yaw / 360.0) * (float) (2 * M_PI)) +
			15 * player->location.y;
	return (vector);
}
