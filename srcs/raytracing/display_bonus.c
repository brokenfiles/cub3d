/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 18:12:50 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_lifebar(t_game *game)
{
	t_vector size;
	int	color;
	t_image *i;

	i = game->image;
	color = convert_rgb(150, 255 / (100 / game->p.health), 55);
	size = vector((game->dim.x / 2) * (game->p.health / 100), 20);
	display_rec(game, form(vector(i->width / 4 - 5, i->height - 40),
			vector(i->width / 2 + 10, 30), 0xFFFBBC), &i);
	display_rec(game, form(vector(i->width / 4, i->height - 35),
			size, color), &i);
	size = vector((i->width / 4) * (game->p.rot_speed / (float)MAX_ROT_SPEED), 5);
	display_rec(game, form(vector((i->width / 4), i->height - 20), size, 0xD56DFF), &i);
	size = vector((i->width / 4) * game->p.speed, 5);
	display_rec(game, form(vector((3 * i->width / 4) - size.x, i->height - 20), size, 0x0000FF), &i);
	return (1);
}

int		display_aim(t_game *game)
{
	display_rec(game, form(vector(game->dim.x / 2 - AIM_WIDTH / 2,
			game->dim.y / 2 - AIM_HEIGHT / 2),
			vector(AIM_WIDTH, AIM_HEIGHT), AIM_COLOR), &game->image);
	display_rec(game, form(vector(game->dim.x / 2 - AIM_HEIGHT / 2,
			game->dim.y / 2 - AIM_WIDTH / 2),
			vector(AIM_HEIGHT, AIM_WIDTH), AIM_COLOR), &game->image);
	display_cir2(game, form(vector(game->dim.x / 2,
			game->dim.y / 2),
			vector(AIM_CIRCLE_SIZE - AIM_CIRCLE_THICK, AIM_CIRCLE_SIZE),
			AIM_CIRCLE_COLOR));
	return (1);
}

int display_map(t_game *game, t_image **image)
{
	int x;
	int y;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			display_rec_trans(game, form(
					vector(game->dim.x / MAP_SIZE * x, game->dim.x / MAP_SIZE * y),
					vector(game->dim.x / MAP_SIZE, game->dim.x / MAP_SIZE),
					ft_strchr("1DH", game->map->map[y][x])? WALL_COLOR : VOID_COLOR), image);
			if (ft_strchr("2LCU", game->map->map[y][x]))
				display_cir2(game, form(vector(game->dim.x / MAP_SIZE * (x + 0.5f), game->dim.x / MAP_SIZE * (y+0.5f)), vector (0,5), 0xFF2B12));
			x++;
		}
		y++;
	}
	return (1);
}

void display_num(t_game *game)
{
	int len;
	int num_1;
	int num_2;
	int num_3;
	char	*tmp;

	tmp = ft_itoa(game->p.coins);
	len = ft_strlen(tmp);
	num_1 = (len >= 1 ? tmp[len - 1] - '0' : 0);
	num_2 = (len >= 2 ? tmp[len - 2] - '0' : 0);
	num_3 = (len >= 3 ? tmp[len - 3] - '0' : 0);
	free(tmp);
	put_image_to_image(game->image, game->map->tex.nbrs[num_3], game->dim.x - 65, 10);
	put_image_to_image(game->image, game->map->tex.nbrs[num_2], game->dim.x - 50, 10);
	put_image_to_image(game->image, game->map->tex.nbrs[num_1], game->dim.x - 35, 10);
}

void display_wallet(t_game *game)
{
	display_rec(game, form(vector(game->dim.x - 100, 5), vector(100, 30), 0x00FFFF), &game->image),
	put_image_to_image(game->image, game->map->tex.co_tex, game->dim.x - 150, -30);
	display_num(game);
}

int display_bonus(t_game *game)
{
	if (!game->disable_bonus)
	{
		display_lifebar(game);
		display_aim(game);
		if (!game->disable_map)
		{
			display_map(game, &game->image);
			display_tri(game, form(vector((game->dim.x / MAP_SIZE) * game->p.pos.x,
						(game->dim.x / MAP_SIZE) * game->p.pos.y),
						vector(game->dim.x / MAP_SIZE + 3, game->dim.x / MAP_SIZE + 3),
								PLAYER_COLOR));
			display_cir2(game, form(vector((game->dim.x / MAP_SIZE) * game->p.pos.x,
								(game->dim.x / MAP_SIZE) * game->p.pos.y),
								vector(0, game->dim.x / MAP_SIZE / 2),
									PLAYER_COLOR));
		}
		display_wallet(game);
	}
	return (1);
}
