/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:24:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/11 03:17:19 by jchotel          ###   ########.fr       */
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
	player.coins_str = (player.coins != 0 ? ft_itoa(player.coins) : "0");
	return (player);
}

void		reinit_player(t_game *game)
{
//TODO : remettre les méchants
	game->p.pos = game->map->spawn;
	game->p.yaw = game->map->spawn_yaw;
	game->p.health = 100;
	game->p.coins = 0;
	game->p.coins_str = (game->p.coins != 0 ? ft_itoa(game->p.coins) : "0");
}

t_game		*init_game(int nb_level, char **av)
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
	game->level = 0;
	game->image->height = 0;
	game->image->width = 0;
	return (game);
}

void 	init_level(t_game *game, int nb_level, char **av)
{//attention protection malloc et free ?
	int i;

	i = 0;
	game->level_names = (char **)malloc(sizeof(char *) * nb_level + 1);
	while (i < nb_level)
	{
		game->level_names[i] = ft_strdup(av[i + 1]);
		//printf("level name : %s\n", game->level_names[i]);
		i++;
	}
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
