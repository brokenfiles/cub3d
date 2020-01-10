/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/10 14:47:41 by jchotel          ###   ########.fr       */
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
{//TODO : mettre la minimap dans une image. Faire une fonction qui permet de combiner deux images
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
					game->map->map[y][x] == '1' ? WALL_COLOR : VOID_COLOR), image);
			if (!ft_strchr("WENSABCD01", game->map->map[y][x]))
				display_cir2(game, form(vector(game->image->width / MAP_SIZE * (x + 0.5f), game->image->width / MAP_SIZE * (y+0.5f)), vector (0,5), 0xFF2B12));
			x++;
		}
		y++;
	}
	return (1);
}

void put_image_to_image(t_image *image, t_image *layer, int x_pos, int y_pos)
{
	int x_l;
	int y_l;

	x_l = 0;
	y_l = 0;
	while (y_l < layer->height)
	{
		while (x_l < layer->width)
		{
			image_set_pixel(image, x_pos + x_l, y_pos + y_l, get_pixel(layer, x_l, y_l).value);
			x_l++;
		}
		x_l = 0;
		y_l++;
	}
}

void load_nbrs(t_game *game)
{
	load_tex(game, &game->map->tex.nbrs[0], "textures/numbers/0.XPM");
	load_tex(game, &game->map->tex.nbrs[1], "textures/numbers/1.XPM");
	load_tex(game, &game->map->tex.nbrs[2], "textures/numbers/2.XPM");
	load_tex(game, &game->map->tex.nbrs[3], "textures/numbers/3.XPM");
	load_tex(game, &game->map->tex.nbrs[4], "textures/numbers/4.XPM");
	load_tex(game, &game->map->tex.nbrs[5], "textures/numbers/5.XPM");
	load_tex(game, &game->map->tex.nbrs[6], "textures/numbers/6.XPM");
	load_tex(game, &game->map->tex.nbrs[7], "textures/numbers/7.XPM");
	load_tex(game, &game->map->tex.nbrs[8], "textures/numbers/8.XPM");
	load_tex(game, &game->map->tex.nbrs[9], "textures/numbers/9.XPM");
}
void display_coins(t_game *game)
{
	load_nbrs(game);
	//printf("1.width %d\n", game->map->tex.nbrs[0]->width);
	//printf("1.height %d\n", game->map->tex.nbrs[0]->height);
//	printf("coins : %d,  char 0 : %c\n", game->p.coins, game->p.coins_str[0]);
	put_image_to_image(game->image, game->map->tex.nbrs[game->p.coins_str[0] - '0'], 200, 200);

	//if (game->p.coins_str[0] == '0')
//		put_image_to_image(game->image, game->map->tex.nbrs[game->p.coins_str[0] - '0'], 200, 200);
//	if (game->p.coins_str[0] == '1')
//		put_image_to_image(game->image, game->map->tex.nbrs[1], 200, 200);
//	if (game->p.coins_str[0] == '2')
//		put_image_to_image(game->image, game->map->tex.nbrs[2], 200, 200);
//	if (game->p.coins_str[0] == '3')
//		put_image_to_image(game->image, game->map->tex.nbrs[3], 200, 200);
//	if (game->p.coins_str[0] == '4')
//	{
//		put_image_to_image(game->image, game->map->tex.nbrs[4], 100, 200);
//	}
//	if (game->p.coins_str[0] == '5')
//		put_image_to_image(game->image, game->map->tex.nbrs[5], 200, 200);
}

int display_bonus(t_game *game)
{
	display_lifebar(game);
	display_aim(game);
	if (!game->disable_map)
	{
		display_map(game, &game->image);
		display_tri(game, form(vector((game->image->width / MAP_SIZE) * game->p.pos.x, (game->image->width / MAP_SIZE) * game->p.pos.y), vector(game->image->width / MAP_SIZE + 3, game->image->width / MAP_SIZE + 3), MINIMAP_PLAYER_COLOR));
		display_circle(game, form(vector((game->image->width / MAP_SIZE) * game->p.pos.x, (game->image->width / MAP_SIZE) * game->p.pos.y), vector(game->image->width / MAP_SIZE / 2, game->image->width / MAP_SIZE / 2), MINIMAP_PLAYER_COLOR), game->image->width / MAP_SIZE / 2);
		image_set_pixel(game->image, (game->image->width / MAP_SIZE) * game->p.pos.x, (game->image->width / MAP_SIZE) * game->p.pos.y, 0xFF4A25);
	}
	display_coins(game);
	return (1);
}