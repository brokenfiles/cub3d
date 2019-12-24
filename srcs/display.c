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
void display_pixel(t_game *game, t_vector *vector, int color)
{
	mlx_pixel_put(game->ptr, game->win, vector->x, vector->y, color);
}

void display_cir(t_game *game, t_form *form)
{
	int r;
	float teta;

	teta = 0;
	while (teta <= (float) (2 * M_PI))
	{
		r = 0;
		while (r <= form->dim->x)
		{
			display_pixel(game, init_vector(r * cos(teta) + form->vector->x, r * sin(teta) + form->vector->y), form->color);
			r++;
		}
		teta += (float)M_PI / (form->dim->x * game->map->tex.size);
	}

	free(form->vector);
	free(form->dim);
	free(form);
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
int display_tri(t_game *game, t_form *form)
{
	int y;
	int x;
	x = form->vector->x;
	y = form->vector->y;
	while (x >= form->vector->x - form->dim->x)
	{
		y = form->vector->y - (form->vector->x - x) / 3;
		while (y <= form->vector->y + (form->vector->x - x) / 3)
		{
			display_pixel(game, rotation_matrice(game->map->tex, game->p, x, y), form->color);
			y++;
		}
		x--;
	}
	free(form->vector);
	free(form->dim);
	free(form);
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
int display_rec(t_game *game, t_form *form, t_image **image)
{
	int y;
	int x;

	x = form->vector->x;
	while (form->vector->x + form->dim->x > x)
	{
		y = form->vector->y;
		while (form->vector->y + form->dim->y > y)
		{
			image_set_pixel(*image, x, y, form->color);
			y++;
		}
		x++;
	}
	free(form->dim);
	free(form->vector);
	free(form);
	return (1);
}

int display_rec_notfilled(t_game *game, t_form *form, t_image **image)
{
	int y;
	int x;

	x = form->vector->x;
	while (form->vector->x + form->dim->x > x)
	{
		y = form->vector->y;
		while (form->vector->y + form->dim->y > y && (x == 0 || x == form->dim->x) && (y == 0 || y == form->dim->y))
		{
			image_set_pixel(*image, x, y, form->color);
			y++;
		}
		x++;
	}
	free(form->dim);
	free(form->vector);
	free(form);
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

int test_line(t_game *game, t_form *form, float x_inter, int wall, float dist)
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
	x = form->vector->x;
	x_im = ft_scale(0.0, 1.0, 0.0, game->map->tex.we_tex->width, x_inter);
	//printf("x_inter : %f, x_im : %f\n",x_inter, x_im);
	while (form->vector->x + form->dim->x > x)
	{
		y = 0;
		while (game->image->height > y)
		{
			y_im = ft_scale(form->vector->y - (form->dim->y / 2),
							form->vector->y + (form->dim->y / 2), 0, game->map->tex.we_tex->height, y);
			if (y >= form->vector->y - (form->dim->y / 2) && y <= form->vector->y + (form->dim->y / 2))
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
	free(form->dim);
	free(form->vector);
	free(form);
	return (1);
}


float sq_dist(t_vector *origin, t_vector *point)
{
	return (pow(point->x - origin->x, 2) + pow(point->y - origin->y, 2));
}

t_vector next_inter(t_vector *p, t_vector vec, float teta, int *wall, t_game *game)
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
	res = (sq_dist(p, &y) > sq_dist(p, &x) ? x : y); //ligne a mettre dans le return

	//image_set_pixel(game->image, res.x*game->map->tex.size, res.y*game->map->tex.size, 0xFFFFFF);
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

t_vector next_hit(t_map *map, t_vector *p, float teta, int *wall, t_game *game)
{
	t_vector	res;

	res = next_inter(p, *p, teta, wall, game);
	while (map->map[(int)(res.y - (p->y > res.y && res.y == (int)res.y ? 0.0001 : 0))][(int)(res.x - (p->x > res.x && res.x == (int)res.x ? 0.0001 : 0))] != '1')
		res = next_inter(p, res, teta, wall, game);
	return (res);
}

int		display_lifebar(t_game *game)
{
	int	percent;
	int	color;

	color = convertRGB(150, 255 / (100 / game->p->health), 55);
	percent = ((game->image->width / 2 - 20) / (100 / game->p->health));
	display_rec(game, init_form(init_vector((game->image->width / 2) - (game->image->width / 2 / 2), game->image->height - 60), init_vector(game->image->width / 2 , 50), 0xFFFBBC), &game->image);
	display_rec(game, init_form(init_vector((game->image->width / 2) - (game->image->width / 2 / 2 - 10), game->image->height - 55), init_vector(percent, 40), color), &game->image);
	return (1);
}

void				render(t_game *game)
{
	t_vector hit;
	float angle;
	int x;
	int wall;
	float dist;
	int color;

	x = 0;
	angle = 30;
	while (angle > -30)
	{
		hit = next_hit(game->map, game->p->pos, (float)game->p->yaw + angle, &wall, game);
		if (wall == 1)
			color = 0xFFFF00;
		else if (wall == 2)
			color = 0x00FFFF;
		else if (wall == 3)
			color = 0xFF00FF;
		else if (wall == 4)
			color = 0x0FFF0F;
		dist = (float)sqrt(sq_dist(game->p->pos, &hit));
		test_line(game, init_form(init_vector(x, game->image->height / 2), init_vector(1, (float) game->image->height / dist), color), (wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y), wall, dist);
		angle -= 60.0 / game->image->width;
		x++;
	}
	display_lifebar(game);
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
			display_rec(game, init_form(
					init_vector(game->map->tex.size * x, game->map->tex.size * y),
					init_vector(game->map->tex.size, game->map->tex.size),
					game->map->map[y][x] == '1' ? game->map->tex.wall_color : game->map->tex.void_color), image);
			//image_set_pixel(*image, game->map->tex.size * x, game->map->tex.size * y, 0x333333); //quadrillage
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * used to display a line
 * @param t_game game
 * @param x
 * @param teta (orientation of the player)
 * @return int (1 = success, 0 = fail)
 */
int display_line(t_game *game, int x, float teta)
{
	float len_x;
	float len_y;
	float dist;
	long int color = 0xF6F4F6;

	len_x = 0;
	len_y = 0;
	while (game->map->map[(int) (game->p->pos->y + len_y)][(int) (game->p->pos->x + len_x)] != '1')
	{
		len_x += cos((teta / 360.0) * (float) (2 * M_PI)) / 200;
		len_y -= sin((teta / 360.0) * (float) (2 * M_PI)) / 200;
	}
	dist = sqrt((pow(len_y, 2) + pow(len_x, 2)));
	centered_line(game, init_form(init_vector(1, (float) game->image->height / dist),
									   init_vector(x, game->image->height / 2), color));
	return (1);
}

/**
 * display the render
 * @param t_game game
 * @return int (1 = success, 0 = fail)
 */
int display_full_range(t_game *game)
{
	int x;
	float teta;

	x = 0;
	teta = game->p->yaw + 30;
	while (x <= game->image->width && teta >= game->p->yaw - 30)
	{
		display_line(game, x, teta);
		x += 1;
		teta -= 60.0 / game->image->width; //angle de vision * 2
	}
	display_map(game, &game->image); //rajoute la map a l'image
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	//mlx_put_image_to_window(game->ptr, game->win, game->map->tex.so_tex->image, 0, 0);
	return (1);
}

/**
 * display a centered line
 * //TODO: define pixel color using the tex
 * @param t_game game
 * @param t_rectangle rectangle
 * @return int (1 = success, 0 = fail)
 */
int centered_line(t_game *game, t_form *form)
{
	int		y;
	int		x;
	float	x_im;
	float	y_im;

	x = form->vector->x;

	x_im = 0;
	while (form->vector->x + form->dim->x > x)
	{
		y = form->vector->y - (form->dim->y / 2);
		while (form->vector->y + (form->dim->y / 2) > y)
		{
			y_im = ft_scale(form->vector->y - (form->dim->y / 2),
							form->vector->y + (form->dim->y / 2), 0, game->map->tex.we_tex->height, y);
			image_set_pixel(game->image, x, y, form->color);//convertRGB(get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.r,
												//		  get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.g,
												//		  get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.b));
			y++;
		}
		x++;
	}
	free(form->dim);
	free(form->vector);
	free(form);
	return (1);
}



