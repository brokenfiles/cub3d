/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/10 16:03:22 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		ft_nbrlen(int nbr, int len, unsigned int unbr)
{
	if (nbr < 0)
		unbr = -nbr;
	while (unbr)
	{
		unbr = unbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	unsigned int	unbr;
	int				len;
	char			*nbr_final;

	len = 0;
	unbr = nbr;
	len = ft_nbrlen(nbr, len, unbr);
	if (!(nbr_final = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (nbr < 0)
	{
		nbr_final[0] = '-';
		unbr = -nbr;
	}
	nbr_final[len] = '\0';
	len--;
	while (unbr >= 10)
	{
		nbr_final[len] = unbr % 10 + '0';
		unbr = unbr / 10;
		len--;
	}
	nbr_final[len] = unbr % 10 + '0';
	return (nbr_final);
}



void		reinit_player(t_game *game)
{ //TODO : Remmettre les coeurs
	game->p.pos = game->map->spawn;
	game->p.yaw = game->map->spawn_yaw;
	game->p.health = 100;
	game->p.coins = 0;
	game->p.coins = 0;
	game->p.coins_str = ft_itoa(game->p.coins);
}

void		regain_life(t_game *game, int x, int y)
{
	if (game->p.health < 100)
		game->p.health = (game->p.health < 100 - 20) ? game->p.health + 20 : 100; //Passer le 20 en #Define
	game->map->map[y][x] = '0';   //replace by #define VOID
}

void		gain_coins(t_game *game, int x, int y)
{

	game->p.coins++;
	game->p.coins_str = ft_itoa(game->p.coins);
	game->map->map[y][x] = '0';
}


void		move_player(t_game *game, int sign)
{
	t_vector new_pos;
	char val;

	new_pos.y = game->p.pos.y + -sign * game->p.speed * sin((game->p.yaw / 360.0) * (float) (2 * M_PI));
	new_pos.x = game->p.pos.x + sign * game->p.speed * cos((game->p.yaw / 360.0) * (float) (2 * M_PI));
	val = game->map->map[(int)new_pos.y][(int)new_pos.x];
	if (val && !(val == '0' || val == 'W' || val == 'E' || val == 'N' || val == 'S' || val == '2')) //est-ce quon peut pas remplacer par ft_strchr() ?
	{
		game->p.health -= 2;
		if (game->p.health <= 0)
			reinit_player(game);
	}
	if (val == '0' || val == 'W' || val == 'E' || val == 'N' || val == 'S' || val == '2') //est-ce quon peut pas remplacer par ft_strchr() ?
	{
		if (val == '2')
		{
			//regain_life(game, (int) new_pos.x, (int) new_pos.y);
			gain_coins(game, (int) new_pos.x, (int) new_pos.y);
		}
		game->p.pos.x = new_pos.x;
		game->p.pos.y = new_pos.y;
	}
}

int			direction_change(t_player *player, float inc)
{
	player->yaw += inc;
	if (player->yaw > 360 || player->yaw <= 0)
		player->yaw = player->yaw > 0 ? player->yaw % 360 : 360;
	return (1);
}

t_vector	rotation_matrice2(t_vector point, t_vector origin, float teta)
{
	t_vector	vector;
	float		alpha;
	float		c;
	float		s;

	alpha = (teta / 360.0) * (float) (2 * M_PI);
	c = -cos(alpha);
	s = -sin(alpha);
	vector.x = (point.x - origin.x) * c +
				(point.y - origin.y) * s + origin.x;
	vector.y = -(point.x - origin.x) * s +
			   (point.y - origin.y) * c +
			   origin.y;
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
			y = (int)(game->p.pos.y + -1 * index * sin((game->p.yaw / 360.0)
																 * (float) (2 * M_PI)));
			x = (int)(game->p.pos.x + 1 * index * cos((game->p.yaw / 360.0)
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
		direction_change(&game->p, game->p.rot_speed);
	else if (key == 0)
	{
		game->p.yaw += 90;
		move_player(game, 1);
		game->p.yaw -= 90;
	}
	else if (key == 2)
	{
		game->p.yaw -= 90;
		move_player(game, 1);
		game->p.yaw += 90;
	}
	else if (key == K_RIGHT || key == 43)
		direction_change(&game->p, -game->p.rot_speed);
	else if (key == 24)
	{
		if (game->p.rot_speed < MAX_ROT_SPEED)
			game->p.rot_speed++;
	}
	else if (key == 27)
	{
		if (game->p.rot_speed > 1)
			game->p.rot_speed--;
	}
	else if (key == 29)
		game->p.rot_speed = 7;
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP || key == 1 || key == 13 || key == 2 || key == 0 ||
			key == 27 || key == 24 || key == 29)
	{
		if (!render(game))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	}
	last_key_code = key;
	return (1);
}