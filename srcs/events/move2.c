/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:17:26 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/17 15:17:47 by llaurent         ###   ########.fr       */
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
		game->p.pos = vec(new_pos.x, new_pos.y);
	}
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

void		look_up_down(t_game *game, int key)
{
	if (key == K_UP && game->p.vision < 3 * game->dim.y / 4)
		game->p.vision += game->dim.y / 70;
	else if (key == K_DOWN && game->p.vision > game->dim.y / 4)
		game->p.vision -= game->dim.y / 70;
}

void		kneel(t_game *game, int key)
{
	static int kneeling;

	if (key == 49 && !kneeling)
	{
		game->p.vision -= game->dim.y / 2;
		kneeling = 1;
	}
	else if (key == 49)
	{
		game->p.vision += game->dim.y / 2;
		kneeling = 0;
	}
}

void		move(t_game *game, int key)
{
	if (key == K_W || key == K_S)
		move_player(game, (key == K_W ? 1 : -1));
	else if (key == K_LEFT || key == K_RIGHT)
		direction_change(&game->p, (key == K_LEFT ? 1 : -1));
	else if (key == K_A || key == K_D)
	{
		game->p.yaw += (key == K_A ? 1 : -1) * 90;
		move_player(game, 1);
		game->p.yaw -= (key == K_A ? 1 : -1) * 90;
	}
	look_up_down(game, key);
	kneel(game, key);
	change_rot_speed(game, key);
	change_speed(game, key);
}
