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

int		test_line(t_game *game, t_form *form, float x_inter, int wall, float dist)
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
	x_im = ft_scale(0.0, 1.0, 0.0, tex->width, x_inter);
	//printf("x_inter : %f, x_im : %f\n",x_inter, x_im);
	while (form->vector->x + form->dim->x > x)
	{
		y = 0;
		while (game->image->height > y)
		{
			y_im = ft_scale(form->vector->y - (form->dim->y / 2),
							form->vector->y + (form->dim->y / 2), 0, tex->height, y);
			if (y >= form->vector->y - (form->dim->y / 2) && y <= form->vector->y + (form->dim->y / 2))
			{
				dist = 255 / (255 / dist);
				color = convertRGB(get_pixel(tex, x_im, y_im).rgba.r - dist, get_pixel(tex, x_im, y_im).rgba.g - dist, get_pixel(tex, x_im, y_im).rgba.b - dist);
			}
			else
			{
				if (y > game->image->height / 2)
				{
					//printf("%f\n", y_im);
//					y_im = y_im / 32.0;
//					color = convertRGB(get_pixel(game->map->tex.no_tex, x_im, y_im).rgba.r, get_pixel(game->map->tex.no_tex, x_im, y_im).rgba.g, get_pixel(game->map->tex.no_tex, x_im, y_im).rgba.b);
					color = game->map->floor_color;
				}
				else
				{
//					color = convertRGB(get_pixel(game->map->tex.sp_tex, x, y).rgba.r - dist, get_pixel(game->map->tex.sp_tex, x, y).rgba.g - dist, get_pixel(game->map->tex.sp_tex, x, y).rgba.b - dist);
					color = game->map->sky_color;
				}
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

t_vector next_hit(t_map *map, t_vector *p, float teta, int *wall, t_game *game)
{
	t_vector	res;
	int			number;
	int			hit_x;
	int			hit_y;

	number = 0;
	if (!map->map[(int)p->y][(int)p->x])
		return (res);
	res = next_inter(p, *p, teta, wall, game);
	hit_y = (int)(res.y - (p->y > res.y && res.y == (int)res.y ? 0.0001 : 0));
	hit_x = (int)(res.x - (p->x > res.x && res.x == (int)res.x ? 0.0001 : 0));
	while (map->map[hit_y][hit_x] && map->map[hit_y][hit_x] != '1')
	{
		res = next_inter(p, res, teta, wall, game);
		number++;
		if (number > 1000)
		{
			quit(EXIT_FAILURE, "Rendering error. (429)");
			return (res);
		}
		hit_y = (int)(res.y - (p->y > res.y && res.y == (int)res.y ? 0.0001 : 0));
		hit_x = (int)(res.x - (p->x > res.x && res.x == (int)res.x ? 0.0001 : 0));
	}
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
			return (quit(EXIT_FAILURE, "Rendering error."));
		if (wall == 1)
			color = 0xFFFF00;
		else if (wall == 2)
			color = 0x00FFFF;
		else if (wall == 3)
			color = 0xFF00FF;
		else if (wall == 4)
			color = 0x0FFF0F;
		dist = (float)sqrt(sq_dist(game->p->pos, &hit));
		if (!test_line(game, init_form(init_vector(x, game->image->height / 2), init_vector(1, (float)(game->image->height / 0.56) / dist), color), (wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y), wall, dist))
			return (quit(EXIT_FAILURE, "Rendering error."));
		angle -= (angle_copy * 2) / game->image->width;
		x++;
	}
	display_lifebar(game);
	if (!game->disable_map)
		display_map(game, &game->image);
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	if (!game->disable_map)
		display_tri(game, init_form(init_vector(game->map->tex.size * game->p->pos->x, game->map->tex.size * game->p->pos->y), init_vector(game->map->tex.size, game->map->tex.size), game->map->tex.p_color));
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



