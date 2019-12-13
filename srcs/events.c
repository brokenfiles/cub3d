/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/13 04:52:17 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_player(t_player *p, int sign)
{
	p->pos->x += sign * p->speed * cos((p->yaw / 360.0) * (float) (2 * M_PI));
	p->pos->y += -sign * p->speed * sin((p->yaw / 360.0) * (float) (2 * M_PI));
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

	if (!(vector = malloc(sizeof(t_vector))))
		return (NULL);
	vector->x = (x - tex.size * player->pos->x) * cos((player->yaw / 360.0) * (float) (2 * M_PI)) +
				(y - tex.size * player->pos->y) * sin((player->yaw / 360.0) * (float) (2 * M_PI)) +
				tex.size * player->pos->x;
	vector->y = -(x - tex.size * player->pos->x) * sin((player->yaw / 360.0) * (float) (2 * M_PI)) +
				(y - tex.size * player->pos->y) * cos((player->yaw / 360.0) * (float) (2 * M_PI)) +
				tex.size * player->pos->y;
	return (vector);
}

int			handle_key(int key, void *param)
{
	t_game *game;

	game = (t_game *) param;
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	else if (key == K_UP || key == 37)
		move_player(game->p, 1);
	else if (key == K_DOWN || key == 35)
		move_player(game->p, -1);
	else if (key == K_LEFT || key == 36)
		direction_change(game->p, game->p->rot_speed);
	else if (key == K_RIGHT || key == 43)
		direction_change(game->p, -game->p->rot_speed);
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP || key == 43 || key == 36 || key == 35 || key == 37)
	{
		//display_full_range(game);
		display_map(game, &game->image);
		mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);

		display_tri(game, init_form(init_vector(game->map->tex.size * game->p->pos->x, game->map->tex.size * game->p->pos->y), init_vector(game->map->tex.size, game->map->tex.size), 0x0));
		display_tri(game, init_form(init_vector(game->map->tex.size * game->p->pos->x, game->map->tex.size * game->p->pos->y), init_vector(game->map->tex.size, game->map->tex.size), game->map->tex.p_color));
	}
	return (1);
}
