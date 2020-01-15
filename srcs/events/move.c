/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		move_player(t_game *game, int sign)
{
	t_vector	new_pos;
	char		val;
	float		teta;

	teta = (game->p.yaw / 360.0) * (float)(2 * M_PI);
	new_pos.y = game->p.pos.y + -sign * game->p.speed * sin(teta);
	new_pos.x = game->p.pos.x + sign * game->p.speed * cos(teta);
	val = game->map->map[(int)new_pos.y][(int)new_pos.x];
	if (val && ft_strchr("21DH", val))
		lose_life(game);
	else
	{
		gain_life(game, (int)new_pos.x, (int)new_pos.y);
		gain_coins(game, (int)new_pos.x, (int)new_pos.y);
		level_up(game, (int)new_pos.x, (int)new_pos.y);
		game->p.pos = vector(new_pos.x, new_pos.y);
	}
}

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

void		change_speed(t_game *game, int key)
{
	if (key == K_DIGIT_9)
		game->p.speed += (game->p.speed + 0.02 < 1 ? 0.02 : 0);
	else if (key == K_DIGIT_8)
		game->p.speed -= (game->p.speed - 0.02 >= 0 ? 0.02 : 0);
	else if (key == K_DIGIT_7)
		game->p.speed = 0.2;
}

void		move(t_game *game, int key)
{
	if (key == K_UP || key == K_W || key == K_DOWN || key == K_S)
		move_player(game, (key == K_UP || key == K_W ? 1 : -1));
	else if (key == K_LEFT || key == K_RIGHT)
		direction_change(&game->p, (key == K_LEFT ? 1 : -1));
	else if (key == K_A || key == K_D)
	{
		game->p.yaw += (key == K_A ? 1 : -1) * 90;
		move_player(game, 1);
		game->p.yaw -= (key == K_A ? 1 : -1) * 90;
	}
	change_rot_speed(game, key);
	change_speed(game, key);
}
