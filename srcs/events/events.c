/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/06 09:52:50 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		move_player(t_game *game, int sign)
{
	int	x;
	int	y;
	int	b;

	y = (int)(game->p->pos.y + -sign * game->p->speed * sin((game->p->yaw / 360.0)
															 * (float) (2 * M_PI)));
	x = (int)(game->p->pos.x + sign * game->p->speed * cos((game->p->yaw / 360.0)
															* (float) (2 * M_PI)));
	b = (game->map->map[y][x] == '0' || game->map->map[y][x] == 'W' || game->map->map[y][x] == 'E' || game->map->map[y][x] == 'N' || game->map->map[y][x] == 'S' || game->map->map[y][x] == '3');
	if (game->map->map[(int)game->p->pos.y][(int)game->p->pos.x] == '3' && game->map->map[y][x] != '3')
		game->map->map[(int)game->p->pos.y][(int)game->p->pos.x] = '2';
	if (game->map->map[y][x] && !(b))
	{
		game->p->health -= 2;
		if (game->p->health <= 0)
		{
			printf("Tu es mort.\n");
			game->p->pos.x = game->map->spawn.y;
			game->p->pos.y = game->map->spawn.x;
			game->p->yaw = game->map->spawn_yaw;
			game->p->health = 100;
		}
		return ;
	}
	if (b)
	{
		game->p->pos.x += sign * game->p->speed * cos((game->p->yaw / 360.0) * (float) (2 * M_PI));
		game->p->pos.y += -sign * game->p->speed * sin((game->p->yaw / 360.0) * (float) (2 * M_PI));
	}
}

int			direction_change(t_player *player, float inc)
{
	player->yaw += inc;
	if (player->yaw > 360 || player->yaw <= 0)
		player->yaw = player->yaw > 0 ? player->yaw % 360 : 360;
	return (1);
}

t_vector	rotation_matrice(t_tex tex, t_game *game, int x, int y)
{
	t_vector	vector;
	float		alpha;
	float		c;
	float		s;

	alpha = (game->p->yaw / 360.0) * (float) (2 * M_PI);
	c = -cos(alpha);
	s = -sin(alpha);
	vector.x = (x - (game->image->width / MAP_SIZE) * game->p->pos.x) * c +
				(y - (game->image->width / MAP_SIZE) * game->p->pos.y) * s +
			game->image->width / MAP_SIZE * game->p->pos.x;
	vector.y = -(x - (game->image->width / MAP_SIZE) * game->p->pos.x) * s +
				(y - (game->image->width / MAP_SIZE) * game->p->pos.y) * c +
			(game->image->width / MAP_SIZE) * game->p->pos.y;
	return (vector);
}

int			handle_key(int key, void *param)
{
	static int	last_key_code;
	t_game		*game;
	int			wall;
	int 		x;
	int 		y;
	int 		index;

	index = 3;
	game = (t_game *)param;
	if (last_key_code == 259 && key == 12)
		quit(game, EXIT_SUCCESS, NULL);
	if (key == K_ESC)
		quit(game, EXIT_SUCCESS, NULL);
	if (key == 14)
	{
		while (index > 0)
		{
			y = (int)(game->p->pos.y + -1 * index * sin((game->p->yaw / 360.0)
																 * (float) (2 * M_PI)));
			x = (int)(game->p->pos.x + 1 * index * cos((game->p->yaw / 360.0)
																* (float) (2 * M_PI)));
			if (game->map->map[y][x] == '2')
			{
				game->map->map[y][x] = '3';
				render(game);
			}
			index--;
		}
	}
	else if (key == K_UP || key == 13)
		move_player(game, 1);
	else if (key == K_DOWN || key == 1)
		move_player(game, -1);
	else if (key == K_LEFT)
		direction_change(game->p, game->p->rot_speed);
	else if (key == 0)
	{
		game->p->yaw += 90;
		move_player(game, 1);
		game->p->yaw -= 90;
	}
	else if (key == 2)
	{
		game->p->yaw -= 90;
		move_player(game, 1);
		game->p->yaw += 90;
	}
	else if (key == K_RIGHT || key == 43)
		direction_change(game->p, -game->p->rot_speed);
	else if (key == 24)
	{
		if (game->p->rot_speed < MAX_ROT_SPEED)
			game->p->rot_speed++;
	}
	else if (key == 27)
	{
		if (game->p->rot_speed > 1)
			game->p->rot_speed--;
	}
	else if (key == 29)
		game->p->rot_speed = 7;
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP || key == 1 || key == 13 || key == 2 || key == 0 ||
			key == 27 || key == 24 || key == 29)
	{
		if (!render(game))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	}
	last_key_code = key;
	return (1);
}