/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 15:54:20 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float sq_dist(t_vector origin, t_vector point)
{
	return (pow(point.x - origin.x, 2) + pow(point.y - origin.y, 2));
}

t_vector next_inter(t_vector p, t_vector vec, float teta, int *wall, t_game *game)
{//TODO : faire une structure ray pour mettre en mémoire plusieurs constantes dont cos, sin et tan
	float c;
	float alpha;
	t_vector x;
	t_vector y;
	t_vector res;

	alpha = (teta / 360.0) * (float)(2 * M_PI);
	c = vec.y + tan(alpha) * vec.x;
	x.x = (int) vec.x + (vec.x == (int) vec.x && cos(alpha) < 0 ? -1 : 0) + (cos(alpha) > 0 ? 1 : 0);
	x.y = -tan(alpha) * (float) x.x + c;
	y.y = (int) vec.y + (vec.y == (int) vec.y && sin(alpha) > 0 ? -1 : 0) + (sin(alpha) > 0 ? 0 : 1);
	y.x = (y.y - c) / -tan(alpha);
	res = (sq_dist(p, y) > sq_dist(p, x) ? x : y); //ligne a mettre dans le return

	//image_set_pixel(game->image, res.x*game->map->tex.size, res.y*game->map->tex.size, 0xACACAC);
	if (res.x == x.x && res.y == x.y && cos(alpha) > 0)
			*wall = 1;
	else if (res.x == x.x && res.y == x.y)
			*wall = 3;
	else if (sin(alpha) > 0)
			*wall = 2;
	else
			*wall = 4;
	return (res);
}

t_vector next_hit(t_map *map, t_vector p, float teta, int *wall, t_game *game)
{
	t_vector	res;
	int			number;
	int			hit_x;
	int			hit_y;

	number = 0;
	if (!map->map[(int)p.y][(int)p.x])
		return (res);
	res = next_inter(p, p, teta, wall, game);
	if (res.x == 0 && res.y == 0)
		return (res);
	hit_y = (int)(res.y - (p.y > res.y && res.y == (int)res.y ? 0.0001 : 0));
	hit_x = (int)(res.x - (p.x > res.x && res.x == (int)res.x ? 0.0001 : 0));
	while (map->map[hit_y][hit_x] && (game->map->map[hit_y][hit_x] == '0' || game->map->map[hit_y][hit_x] == 'W' || game->map->map[hit_y][hit_x] == 'E' || game->map->map[hit_y][hit_x] == 'N' || game->map->map[hit_y][hit_x] == 'S'))
	{
		if (!ft_strchr("WENS01", map->map[hit_y][hit_x]))
		{
			quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR_428);
			return (res);
		}
		res = next_inter(p, res, teta, wall, game);
		number++;
		if (number > 1000)
		{
			quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR_429);
			return (res);
		}
		hit_y = (int)(res.y - (p.y > res.y && res.y == (int)res.y ? 0.0001 : 0));
		hit_x = (int)(res.x - (p.x > res.x && res.x == (int)res.x ? 0.0001 : 0));
		if (map->map[hit_y][hit_x] == '2')
		{
			*wall = 6;
		}
	}
	return (res);
}

int		set_pixel_transparent(t_game *game, t_vector pos, t_color color, float alpha)
{
	t_color	last_pixel;

	last_pixel = get_pixel(game->image, pos.x, pos.y);
	last_pixel.rgba.r = ((alpha * last_pixel.rgba.r) / 255) + (((255 - alpha) * color.rgba.r) / 255);
	last_pixel.rgba.g = ((alpha * last_pixel.rgba.g) / 255) + (((255 - alpha) * color.rgba.g) / 255);
	last_pixel.rgba.b = ((alpha * last_pixel.rgba.b) / 255) + (((255 - alpha) * color.rgba.b) / 255);
	image_set_pixel(game->image, pos.x, pos.y, last_pixel.value);
	return (1);
}

int		display_lifebar(t_game *game)
{
	int	percent;
	int	color;

	color = convertRGB(150, 255 / (100 / game->p->health), 55);
	percent = ((game->image->width / 2 - 20) / (100 / game->p->health)); // je calcule un pourcentage responsive
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4), game->image->height - 60), vector(game->image->width / 2 , 50), 0xFFFBBC), &game->image);
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4 - 10), game->image->height - 55), vector(percent, 40), color), &game->image);
	percent = ((game->image->width / 2 - 20) / (float)((float)MAX_ROT_SPEED / (float)game->p->rot_speed));
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4 - 10), game->image->height - 20), vector(percent, 5), 0xD56DFF), &game->image);
	return (1);
}

int				render(t_game *game)
{
	t_vector hit;
	float angle;
	float angle_copy;
	int x;
	int wall;
	float dist;
	int color;

	x = 0;
	angle = game->image->width * 0.020833333; //0.020833333 responsive, c'est la division qui permet d'avoir un angle toujours à peu près bon pour que le rendu soit carré
	angle_copy = angle;
	while (angle > -angle_copy)
	{
		hit = next_hit(game->map, game->p->pos, (float)game->p->yaw + angle, &wall, game);
		if (hit.x == 0 && hit.y == 0)
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		dist = (float)sqrt(sq_dist(game->p->pos, hit));
		if (!test_line(game, form(vector(x, game->image->height / 2), vector(1, (float)(game->image->height / 0.56) / dist), color), (wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y), wall, dist))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		angle -= (angle_copy * 2) / game->image->width;
		x++;
	}
	display_lifebar(game);
	if (!game->disable_map)
		display_map(game, &game->image);
	display_aim(game);
	if (!game->disable_map)
	{
		display_tri(game, form(vector((game->image->width / MAP_SIZE) * game->p->pos.x, (game->image->width / MAP_SIZE) * game->p->pos.y), vector(game->image->width / MAP_SIZE + 3, game->image->width / MAP_SIZE + 3), MINIMAP_PLAYER_COLOR));
		display_circle(game, form(vector((game->image->width / MAP_SIZE) * game->p->pos.x, (game->image->width / MAP_SIZE) * game->p->pos.y), vector(game->image->width / MAP_SIZE / 2, game->image->width / MAP_SIZE / 2), MINIMAP_PLAYER_COLOR), game->image->width / MAP_SIZE / 2);
		image_set_pixel(game->image, (game->image->width / MAP_SIZE) * game->p->pos.x, (game->image->width / MAP_SIZE) * game->p->pos.y, 0xFF4A25);
	}
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	if (game->save_first_image)
	{
		game->save_first_image = 0;
		if (!save_bitmap(game, "screenshot.bmp"))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	}
	return (1);
}

/**
 * used to display the map
 * @param t_data data
 * @param t_map map
 * @param t_player player
 * @return int (1 = success, 0 = fail)
 */
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
					vector(game->image->width / MAP_SIZE * x, game->image->width / MAP_SIZE * y),
					vector(game->image->width / MAP_SIZE, game->image->width / MAP_SIZE),
					game->map->map[y][x] == '1' ? game->map->tex.wall_color : game->map->tex.void_color), image);
			if (!ft_strchr("WENS01", game->map->map[y][x]))
				display_circle(game, form(vector(game->image->width / MAP_SIZE * x, game->image->width / MAP_SIZE * y),
						vector(game->image->width / MAP_SIZE, game->image->width / MAP_SIZE), 0xFF2B12),
								game->image->width / MAP_SIZE);
			x++;
		}
		y++;
	}
	return (1);
}


