/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 11:26:56 by llaurent         ###   ########.fr       */
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
	float alpha;

	alpha = (player->yaw / 360.0) * (float) (2 * M_PI);
	if (!(vector = malloc(sizeof(t_vector))))
		return (NULL);
	vector->x = (x - tex.size * player->pos->x) * cos(alpha) +
				(y - tex.size * player->pos->y) * sin(alpha) +
				tex.size * player->pos->x;
	vector->y = -(x - tex.size * player->pos->x) * sin(alpha) +
				(y - tex.size * player->pos->y) * cos(alpha) +
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
		display_map(game, &game->image);
		mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);

		display_tri(game, init_form(init_vector(game->map->tex.size * game->p->pos->x, game->map->tex.size * game->p->pos->y), init_vector(game->map->tex.size, game->map->tex.size), 0x0));
		display_tri(game, init_form(init_vector(game->map->tex.size * game->p->pos->x, game->map->tex.size * game->p->pos->y), init_vector(game->map->tex.size, game->map->tex.size), game->map->tex.p_color));

		//t_vector next = next_inter(game->p->pos, *game->p->pos, game->p->yaw, &wall);

		float index = game->p->yaw;
		while (index < game->p->yaw + 30)
		{
			t_vector next = next_hit(game->map, game->p->pos, index, &wall, game);
			mlx_pixel_put(game->ptr, game->win, next.x*game->map->tex.size, next.y*game->map->tex.size, 0xFFFFFF);
			index += 0.5;
		}
		index = game->p->yaw;
		while (index > game->p->yaw - 30)
		{
			t_vector next = next_hit(game->map, game->p->pos, index, &wall, game);
			mlx_pixel_put(game->ptr, game->win, next.x*game->map->tex.size, next.y*game->map->tex.size, 0xFFFFFF);
			index -= 0.5;
		}
		//printf("pos x : %f,  pos y : %f,  angle : %d  next x : %f  next y :  %f wall : %d\n", game->p->pos->x, game->p->pos->y, game->p->yaw, next.x, next.y, wall);
	}
	last_key_code = key;
	return (1);
}