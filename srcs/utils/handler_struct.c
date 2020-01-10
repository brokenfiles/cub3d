/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:24:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/10 19:43:58 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_player	init_player(void)
{
	t_player	player;

	player.rot_speed = 4;
	player.speed = 0.5;
	player.health = 100;
	player.size = 1;
	player.coins = 0;
	player.coins_str = ft_itoa(player.coins);
	return (player);
}

void		reinit_player(t_game *game)
{
//TODO : remettre les méchants
	game->p.pos = game->map->spawn;
	game->p.yaw = game->map->spawn_yaw;
	game->p.health = 100;
	game->p.coins = 0;
	game->p.coins_str = ft_itoa(game->p.coins);
}

t_game		*init_game(void)
{
	t_game	*game;

	if (!(game = malloc(sizeof(struct s_game))))
		return (NULL);
	if (!(game->image = malloc(sizeof(struct s_image))))
		return (NULL);
	if (!(game->map = malloc(sizeof(struct s_map))))
		return (NULL);
	game->ptr = NULL;
	game->win = NULL;
	game->p = init_player();
	game->image->height = 0;
	game->image->width = 0;
	return (game);
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
