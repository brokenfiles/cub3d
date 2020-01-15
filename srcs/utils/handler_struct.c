/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:24:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_player	init_player(void)
{
	t_player	player;

	player.rot_speed = 5;
	player.speed = 0.2;
	player.health = 100;
	player.size = 1;
	player.coins = 0;
	return (player);
}

void		reinit_player(t_game *game)
{
//TODO : remettre les méchants
	game->p.pos = game->map->spawn;
	game->p.yaw = game->map->spawn_yaw;
	game->p.health = 100;
	game->p.coins = 0;
}

int			set_ray(t_ray *ray, float teta)
{
	ray->alpha = (teta / 360.0) * (float)(2 * M_PI);
	ray->cos = cos(ray->alpha);
	ray->sin = sin(ray->alpha);
	ray->tan = tan(ray->alpha);
	return (1);
}

t_game		*init_game(int nb_level, char **av)
{
	t_game	*game;

	if (!(game = malloc(sizeof(struct s_game))))
		return (NULL);
	if (!(game->map = malloc(sizeof(struct s_map))))
		return (NULL);
	game->p = init_player();
	game->level = 0;
	game->total_level = 0;
	game->dim.y = 0;
	game->dim.x = 0;
	game->disable_map = 0;
	game->disable_bonus = 0;
	game->save_first_image = 0;
	return (game);
}

t_sprite	init_sprite()
{
	t_sprite	sprite;

	sprite.defined = 0;
	sprite.pos.x = -1;
	sprite.pos.y = -1;
	sprite.wall = -1;
	return (sprite);
}

t_vector	vector(float x, float y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_form		form(t_vector vector, t_vector dim, int color)
{
	t_form	form;

	form.dim = dim;
	form.vector = vector;
	form.color = color;
	return (form);
}
