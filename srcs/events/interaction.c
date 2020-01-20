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

void		gain_life(t_game *game, int x, int y)
{
	if (game->map->map[y][x] == 'L')
	{
		if (game->p.health < 100)
			game->p.health = game->p.health < 100 - HP ?
					game->p.health + HP : 100;
		game->map->map[y][x] = '0';
	}
}

void		lose_life(t_game *game)
{
	game->p.health -= 2;
	if (game->p.health <= 0)
		reinit_player(game);
}

void		gain_coins(t_game *game, int x, int y)
{
	if (game->map->map[y][x] == 'C')
	{
		game->p.coins++;
		game->map->map[y][x] = '0';
	}
}

void		level_up(t_game *game, int x, int y)
{
	if (game->map->map[y][x] == 'U')
		game->level++;
}

void		interact(t_game *game, int key)
{
	int	steps;
	int	x;
	int	y;

	if (key == K_E)
	{
		steps = 3;
		while (steps > 0)
		{
			y = (int)(game->p.pos.y + -1 * steps * sin(
					(game->p.yaw / 360.0) * (float)(2 * M_PI)));
			x = (int)(game->p.pos.x + 1 * steps * cos(
					(game->p.yaw / 360.0) * (float)(2 * M_PI)));
			if (game->map->map[y][x] == '1')
				return ;
			if (game->map->map[y][x] == '2')
				game->map->map[y][x] = '3';
			if (game->map->map[y][x] == 'D')
				game->map->map[y][x] = 'B';
			if (game->map->map[y][x] == 'H')
				game->map->map[y][x] = 'F';
			steps--;
		}
	}
}
