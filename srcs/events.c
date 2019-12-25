/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 16:55:22 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_player(t_game *game, int sign)
{
	int	x;
	int	y;

	y = (int)(game->p->pos->y + -sign * game->p->speed * sin((game->p->yaw / 360.0)
															 * (float) (2 * M_PI)));
	x = (int)(game->p->pos->x + sign * game->p->speed * cos((game->p->yaw / 360.0)
															* (float) (2 * M_PI)));
	if (!game->map->map[y][x])
		return ;
	if (game->map->map[y][x] && game->map->map[y][x] == '1')
	{
		game->p->health -= 2;
		if (game->p->health <= 0)
		{
			printf("Tu es mort.\n");
			game->p->pos->x = game->map->spawn->y;
			game->p->pos->y = game->map->spawn->x;
			game->p->yaw = game->map->spawn_yaw;
			game->p->health = 100;
		}
		return ;
	}
	game->p->pos->x += sign * game->p->speed * cos((game->p->yaw / 360.0) * (float) (2 * M_PI));
	game->p->pos->y += -sign * game->p->speed * sin((game->p->yaw / 360.0) * (float) (2 * M_PI));
}

int			direction_change(t_player *player, float inc)
{
	player->yaw += inc;
	if (player->yaw > 360 || player->yaw <= 0)
		player->yaw = player->yaw > 0 ? player->yaw % 360 : 360;
	return (1);
}

t_vector	*rotation_matrice(t_tex tex, t_player *player, int x, int y)
{
	t_vector *vector;
	float alpha;
	float c;
	float s;

	alpha = (player->yaw / 360.0) * (float) (2 * M_PI);
	c = cos(alpha);
	s = sin(alpha);
	if (!(vector = malloc(sizeof(t_vector))))
		return (NULL);
	vector->x = (x - tex.size * player->pos->x) * c +
				(y - tex.size * player->pos->y) * s +
				tex.size * player->pos->x;
	vector->y = -(x - tex.size * player->pos->x) * s +
				(y - tex.size * player->pos->y) * c +
				tex.size * player->pos->y;
	return (vector);
}

int			handle_key(int key, void *param)
{
	static int	last_key_code;
	t_game		*game;
	int			wall;
	game = (t_game *)param;

	if (last_key_code == 259 && key == 12)
		exit(EXIT_SUCCESS);
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
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
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP || key == 1 || key == 13 || key == 2 || key == 0)
	{
		if (!render(game))
			return (quit(EXIT_FAILURE, "Rendering error."));
	}
	last_key_code = key;
	return (1);
}