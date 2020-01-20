/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:30:14 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:30:14 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			direction_change(t_player *player, int sign)
{
	player->yaw += sign * player->rot_speed;
	if (player->yaw > 360 || player->yaw <= 0)
		player->yaw = player->yaw > 0 ? player->yaw % 360 : 360;
	return (1);
}

void		change_rot_speed(t_game *game, int key)
{
	if (key == K_PLUS)
	{
		if (game->p.rot_speed < MAX_ROT_SPEED)
			game->p.rot_speed++;
	}
	else if (key == K_MINUS)
	{
		if (game->p.rot_speed > 1)
			game->p.rot_speed--;
	}
	else if (key == K_DIGIT_0)
		game->p.rot_speed = 7;
}
