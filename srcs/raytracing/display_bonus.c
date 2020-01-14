/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/14 08:17:43 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_lifebar(t_game *game)
{
	int	percent;
	int	color;

	color = convert_rgb(150, 255 / (100 / game->p.health), 55);
	percent = ((game->image->width / 2 - 20) / (100 / game->p.health)); // je calcule un pourcentage responsive
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4), game->image->height - 60), vector(game->image->width / 2 , 50), 0xFFFBBC), &game->image);
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4 - 10), game->image->height - 55), vector(percent, 40), color), &game->image);
	percent = ((game->image->width / 2 - 20) / (float)((float)MAX_ROT_SPEED / (float)game->p.rot_speed));
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4 - 10), game->image->height - 20), vector(percent, 5), 0xD56DFF), &game->image);
	return (1);
}

int		display_aim(t_game *game)
{
	display_rec(game, form(vector(game->image->width / 2, game->image->height / 2 - AIM_HEIGHT + AIM_WIDTH / 2 + 8), vector(AIM_WIDTH, AIM_HEIGHT), AIM_COLOR), &game->image);
	display_rec(game, form(vector(game->image->width / 2 - AIM_HEIGHT / 2, game->image->height / 2 - AIM_HEIGHT / 2 + 8), vector(AIM_HEIGHT, AIM_WIDTH), AIM_COLOR), &game->image);
	display_circle(game, form(vector(game->image->width / 2, game->image->height / 2 - AIM_HEIGHT / 2 + 8), vector(AIM_CIRCLE_SIZE, AIM_CIRCLE_SIZE), AIM_CIRCLE_COLOR), AIM_CIRCLE_THICK); //remplacer par la focntion display_cir
	return (1);
}

int display_map(t_game *game, t_image **image)
{//TODO : mettre la minimap dans une image.
	// TODO: afficher seulement les parties connues de la carte
	int x;
	int y;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			display_rec_trans(game, form(
					vector(game->image->width / MAP_SIZE * x, game->image->width / MAP_SIZE * y),
					vector(game->image->width / MAP_SIZE, game->image->width / MAP_SIZE),
					ft_strchr("1DH", game->map->map[y][x])? WALL_COLOR : VOID_COLOR), image);
			if (ft_strchr("2LCU", game->map->map[y][x]))
				display_cir2(game, form(vector(game->image->width / MAP_SIZE * (x + 0.5f), game->image->width / MAP_SIZE * (y+0.5f)), vector (0,5), 0xFF2B12));
			x++;
		}
		y++;
	}
	return (1);
}

void put_image_to_image(t_image *image, t_image *layer, int x_pos, int y_pos)
{//verifier quon ne depasse pas la taille de l'image
	int x_l;
	int y_l;
	int value;

	x_l = 0;
	y_l = 0;
	while (y_l < layer->height && y_pos + y_l < image->height)
	{
		while (x_l < layer->width && x_pos + x_l < image->width)
		{
			value = get_pixel(layer, x_l, y_l).value;
			value != -16777216 ? image_set_pixel(image, x_pos + x_l, y_pos + y_l, value) : 0;
			x_l++;
		}
		x_l = 0;
		y_l++;
	}
}

void display_num(t_game *game)
{
	int len;
	int num_1;
	int num_2;
	int num_3;

	len = ft_strlen(game->p.coins_str);
	num_1 = (len >= 1 ? game->p.coins_str[len - 1] - '0' : 0);
	num_2 = (len >= 2 ? game->p.coins_str[len - 2] - '0' : 0);
	num_3 = (len >= 3 ? game->p.coins_str[len - 3] - '0' : 0);
	put_image_to_image(game->image, game->map->tex.nbrs[num_3], game->image->width - 65, 10);
	put_image_to_image(game->image, game->map->tex.nbrs[num_2], game->image->width - 50, 10);
	put_image_to_image(game->image, game->map->tex.nbrs[num_1], game->image->width - 35, 10);
}

void display_wallet(t_game *game)
{
	display_rec(game, form(vector(game->image->width - 100, 5), vector(100, 30), 0x00FFFF),  &game->image),
	put_image_to_image(game->image, game->map->tex.co_tex, game->image->width - 150, -30);
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
			display_tri(game, form(vector((game->image->width / MAP_SIZE) * game->p.pos.x,
										  (game->image->width / MAP_SIZE) * game->p.pos.y),
								   vector(game->image->width / MAP_SIZE + 3, game->image->width / MAP_SIZE + 3),
								   PLAYER_COLOR));
			display_circle(game, form(vector((game->image->width / MAP_SIZE) * game->p.pos.x,
											 (game->image->width / MAP_SIZE) * game->p.pos.y),
									  vector(game->image->width / MAP_SIZE / 2, game->image->width / MAP_SIZE / 2),
									  PLAYER_COLOR), game->image->width / MAP_SIZE / 2);
		}
		display_wallet(game);
	}
	return (1);
}