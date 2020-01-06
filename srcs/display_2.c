
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
			image_set_pixel(game->image, rotation_matrice(game->map->tex, game, x, y).x, rotation_matrice(game->map->tex, game, x, y).y, form.color);
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

int display_rec_trans(t_game *game, t_form form, t_image **image)
{
	int y;
	int x;

	x = form.vector.x;
	while (form.vector.x + form.dim.x > x)
	{
		y = form.vector.y;
		while (form.vector.y + form.dim.y > y)
		{
			set_pixel_transparent(game, vector(x, y), c(form.color), 100);
			y++;
		}
		x++;
	}
	return (1);
}

int		display_circle(t_game *game, t_form circle, float thick)
{
	float	dist;
	int		x;
	int		y;

	x = 0;
	while (x <= 2 * circle.dim.x)
	{
		y = 0;
		while (y <= 2 * circle.dim.y)
		{
			dist = sqrt((x - circle.dim.x) * (x - circle.dim.x) +
						(y - circle.dim.x) * (y - circle.dim.x));
			if (dist > circle.dim.x - thick && dist < circle.dim.y)
				image_set_pixel(game->image, x + circle.vector.x - circle.dim.x, y + circle.vector.y - circle.dim.x, circle.color);
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
	int		tex_height, c_1, c_2;
	t_image *tex;

	if (wall == 1)
		tex = game->map->tex.we_tex;
	if (wall == 2)
		tex = game->map->tex.no_tex;
	if (wall == 3)
		tex = game->map->tex.ea_tex;
	if (wall == 4)
		tex = game->map->tex.so_tex;
	if (wall == 6)
		tex = game->map->tex.sp_tex;
	x = form.vector.x;
	x_im = ft_scale(0.0, 1.0, 0.0, tex->width, x_inter);
	tex_height = tex->height;
	c_1 = form.vector.y - (form.dim.y / 2);
	c_2 = form.vector.y + (form.dim.y / 2);
	while (form.vector.x + form.dim.x > x)
	{
		y = 0;
		while (game->image->height > y)
		{
			y_im = ft_scale(c_1, c_2, 0, tex_height, y);
			if (y >= form.vector.y - (form.dim.y / 2) && y <= form.vector.y + (form.dim.y / 2))
			{
//				dist = 255 / (255 / dist);
				color = get_pixel(tex, x_im, y_im).value;
//				color = convertRGB(get_pixel(tex, x_im, y_im).rgba.r - dist, get_pixel(tex, x_im, y_im).rgba.g - dist, get_pixel(tex, x_im, y_im).rgba.b - dist);
//				image_set_pixel(game->image, x, y, color);
			}
			else
			{
				if (y > game->image->height / 2)
					color = game->map->floor_color;
				else
					color = game->map->sky_color;
			}
//			if (get_pixel(game->image, x, y).value != color)
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
