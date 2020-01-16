/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/16 10:18:55 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_lifebar(t_game *game, int t)
{
	t_vector	size;
	int			color;
	t_image		*i;

	i = game->image;
	color = convert_rgb(150, 255 / (100 / game->p.health), 55);
	size = vec((game->dim.x / 2) * (game->p.health / 100), 20);
	display_rec(game, form(vec(i->w / 4 - 5, i->h - 40),
			vec(i->w / 2 + 10, 30), 0xFFFBBC), &i, t);
	display_rec(game, form(vec(i->w / 4, i->h - 35),
			size, color), &i, t);
	size = vec((i->w / 4) * (game->p.rot_speed / (float)MAX_ROT_SPEED), 5);
	display_rec(game, form(vec((i->w / 4), i->h - 20),
			size, 0xD56DFF), &i, t);
	size = vec((i->w / 4) * game->p.speed, 5);
	display_rec(game, form(vec((3 * i->w / 4) - size.x, i->h - 20),
			size, 0x0000FF), &i, t);
	return (1);
}

int		display_aim(t_game *game)
{
	display_rec(game, form(vec(game->dim.x / 2 - AIM_WIDTH / 2,
			game->dim.y / 2 - AIM_HEIGHT / 2),
			vec(AIM_WIDTH, AIM_HEIGHT), AIM_COLOR), &game->image, 0);
	display_rec(game, form(vec(game->dim.x / 2 - AIM_HEIGHT / 2,
			game->dim.y / 2 - AIM_WIDTH / 2),
			vec(AIM_HEIGHT, AIM_WIDTH), AIM_COLOR), &game->image, 0);
	display_cir2(game, form(vec(game->dim.x / 2,
			game->dim.y / 2),
			vec(AIM_CIRCLE_SIZE - AIM_CIRCLE_THICK, AIM_CIRCLE_SIZE),
			AIM_CIRCLE_COLOR), 0);
	return (1);
}

void	display_num(t_game *game)
{
	int		len;
	int		num_1;
	int		num_2;
	int		num_3;
	char	*tmp;

	tmp = ft_itoa(game->p.coins);
	len = ft_strlen(tmp);
	num_1 = (len >= 1 ? tmp[len - 1] - '0' : 0);
	num_2 = (len >= 2 ? tmp[len - 2] - '0' : 0);
	num_3 = (len >= 3 ? tmp[len - 3] - '0' : 0);
	free(tmp);
	put_image_to_image(game->image, game->map->tex.nbrs[num_3],
			game->dim.x - 65, 10);
	put_image_to_image(game->image, game->map->tex.nbrs[num_2],
			game->dim.x - 50, 10);
	put_image_to_image(game->image, game->map->tex.nbrs[num_1],
			game->dim.x - 35, 10);
}

void	display_wallet(t_game *game)
{
	display_rec(game, form(vec(game->dim.x - 100, 5),
			vec(100, 30), 0x00FFFF), &game->image, 0);
	put_image_to_image(game->image, game->map->tex.co_tex,
			game->dim.x - 150, -30);
	display_num(game);
}

int		display_bonus(t_game *game, int t)
{
	if (!game->disable_bonus)
	{
		display_lifebar(game, t);
		display_aim(game);
		if (!game->disable_map)
		{
			display_map(game, &game->image, t);
			display_tri(game, form(vec((game->dim.x / MAP_SIZE) * game->p.pos.x,
				(game->dim.x / MAP_SIZE) * game->p.pos.y),
				vec(game->dim.x / MAP_SIZE + 3, game->dim.x / MAP_SIZE + 3),
				PLAYER_COLOR));
			display_cir2(game, form(vec((game->dim.x / MAP_SIZE)
				* game->p.pos.x, (game->dim.x / MAP_SIZE) * game->p.pos.y),
				vec(0, game->dim.x / MAP_SIZE / 2),
				PLAYER_COLOR), 240);
		}
		display_wallet(game);
	}
	return (1);
}
