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

/**
 * display pixel but DEPRECIATED!
 * @deprecated
 * @param t_data data
 * @param t_vector vector
 * @param int color
 */
void display_pixel(t_game *game, t_vector vector, int color)
{
	mlx_pixel_put(game->ptr, game->win, vector.x, vector.y, color);
}

/**
 * used to display a triangle
 * TODO: change pixelput to images
 * @deprecated for now
 * @param t_data data
 * @param t_player player
 * @param t_triangle triangle
 * @return int (1 = success, 0 = fail)
 */
int display_tri(t_game *game, t_form form)
{
	int y;
	int x;
	x = form.vector.x;
	y = form.vector.y;
	while (x >= form.vector.x - form.dim.x)
	{
		y = form.vector.y - (form.vector.x - x) / 3;
		while (y <= form.vector.y + (form.vector.x - x) / 3)
		{
			display_pixel(game, rotation_matrice(game->map->tex, game, x, y), form.color);
			y++;
		}
		x--;
	}
	return (1);
}

/**
 * used to display a rectangle but with images
 * //TODO: define pixel color using the tex
 * @apprecieted
 * @param t_game game
 * @param t_rectangle rectangle
 * @return int (1 = success, 0 = fail)
 */
int display_rec(t_game *game, t_form form, t_image **image)
{
	int y;
	int x;

	x = form.vector.x;
	while (form.vector.x + form.dim.x > x)
	{
		y = form.vector.y;
		while (form.vector.y + form.dim.y > y)
		{
			image_set_pixel(*image, x, y, form.color);
			y++;
		}
		x++;
	}
	return (1);
}

int ft_scale(int ymin, int ymax, int nmin, int nmax, float y)
{
	float k;
	float c;

	k = (float) (nmax - nmin) / (ymax - ymin);
	c = (float) nmin - (float) k * ymin;
	return ((k * y + c));
}

int		test_line(t_game *game, t_form form, float x_inter, int wall, float dist)
{
	int		y;
	int		x;
	float	x_im;
	float	y_im;
	int color;
	t_image *tex;

	if (wall == 1)
		tex = game->map->tex.we_tex;
	if (wall == 2)
		tex = game->map->tex.no_tex;
	if (wall == 3)
		tex = game->map->tex.ea_tex;
	if (wall == 4)
		tex = game->map->tex.so_tex;
	x = form.vector.x;
	x_im = ft_scale(0.0, 1.0, 0.0, tex->width, x_inter);
	while (form.vector.x + form.dim.x > x)
	{
		y = 0;
		while (game->image->height > y)
		{
			y_im = ft_scale(form.vector.y - (form.dim.y / 2),
							form.vector.y + (form.dim.y / 2), 0, tex->height, y);
			if (y >= form.vector.y - (form.dim.y / 2) && y <= form.vector.y + (form.dim.y / 2))
			{
				dist = 255 / (255 / dist);
				color = convertRGB(get_pixel(tex, x_im, y_im).rgba.r - dist, get_pixel(tex, x_im, y_im).rgba.g - dist, get_pixel(tex, x_im, y_im).rgba.b - dist);
			}
			else
			{
				if (y > game->image->height / 2)
					color = game->map->floor_color;
				else
					color = game->map->sky_color;
			}
			image_set_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
	return (1);
}

int		display_aim(t_game *game)
{
	display_rec(game, form(vector(game->image->width / 2, game->image->height / 2 - AIM_HEIGHT + AIM_WIDTH / 2), vector(AIM_WIDTH, AIM_HEIGHT), AIM_COLOR), &game->image);
	display_rec(game, form(vector(game->image->width / 2 - AIM_HEIGHT / 2, game->image->height / 2 - AIM_HEIGHT / 2), vector(AIM_HEIGHT, AIM_WIDTH), AIM_COLOR), &game->image);
	return (1);
}

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
	}
	return (res);
}

int		display_lifebar(t_game *game)
{
	int	percent;
	int	color;

	color = convertRGB(150, 255 / (100 / game->p->health), 55);
	percent = ((game->image->width / 2 - 20) / (100 / game->p->health));
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4), game->image->height - 60), vector(game->image->width / 2 , 50), 0xFFFBBC), &game->image);
	display_rec(game, form(vector((game->image->width / 2) - (game->image->width / 4 - 10), game->image->height - 55), vector(percent, 40), color), &game->image);
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
	angle = game->image->width * 0.020833333;
	angle_copy = angle;
	while (angle > -angle_copy)
	{
		hit = next_hit(game->map, game->p->pos, (float)game->p->yaw + angle, &wall, game);
		if (hit.x == 0 && hit.y == 0)
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		if (wall == 1)
			color = 0xFFFF00;
		else if (wall == 2)
			color = 0x00FFFF;
		else if (wall == 3)
			color = 0xFF00FF;
		else if (wall == 4)
			color = 0x0FFF0F;
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
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	if (!game->disable_map)
		display_tri(game, form(vector((game->image->width / 240) * game->p->pos.x, (game->image->width / 240) * game->p->pos.y), vector(game->image->width / 240, game->image->width / 240), game->map->tex.p_color));
	if (game->save_first_image)
	{
		game->save_first_image = 0;
		if (!save_bitmap(game, "screenshot.bmp"))
			return (0);
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
			display_rec(game, form(
					vector(game->image->width / 240 * x, game->image->width / 240 * y),
					vector(game->image->width / 240, game->image->width / 240),
					game->map->map[y][x] == '1' ? game->map->tex.wall_color : game->map->tex.void_color), image);
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * display a centered line
 * //TODO: define pixel color using the tex
 * @param t_game game
 * @param t_rectangle rectangle
 * @return int (1 = success, 0 = fail)
 */
int centered_line(t_game *game, t_form form)
{
	int		y;
	int		x;
	float	x_im;
	float	y_im;

	x = form.vector.x;

	x_im = 0;
	while (form.vector.x + form.dim.x > x)
	{
		y = form.vector.y - (form.dim.y / 2);
		while (form.vector.y + (form.dim.y / 2) > y)
		{
			y_im = ft_scale(form.vector.y - (form.dim.y / 2),
							form.vector.y + (form.dim.y / 2), 0, game->map->tex.we_tex->height, y);
			image_set_pixel(game->image, x, y, form.color);//convertRGB(get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.r,
												//		  get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.g,
												//		  get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.b));
			y++;
		}
		x++;
	}
	return (1);
}



