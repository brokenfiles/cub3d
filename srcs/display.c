/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/13 00:59:38 by llaurent         ###   ########.fr       */
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
			display_pixel(game, rotation_matrice(game->p, x, y), form->color);
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
	while (form->vector->x + form->dim->x - x > 0)
	{
		y = form->vector->y;
		while (form->vector->y + form->dim->y - y > 0)
		{
			if (form->color == -1)
			{
				image_set_pixel(*image, x, y,
								clerp(c(0x0), get_pixel(game->map->tex.no_tex, x % 30, y % 30), x).value);
			}
			else if (form->color == -2)
			{
				image_set_pixel(*image, x, y,
								clerp(c(0x0), get_pixel(game->map->tex.so_tex, x % 30, y % 30), 1.0f).value);
			}
			else
			{
				image_set_pixel(*image, x, y, form->color);
			}
			y++;
		}
		x++;
	}
	free(form->dim);
	free(form->vector);
	free(form);
	return (1);
}

int ft_scale(int ymin, int ymax, int nmin, int nmax, int y)
{
	float k;
	float c;

	k = (float) (nmax - nmin) / (ymax - ymin);
	c = (float) nmin - (float) k * ymin;
	return ((int) (k * y + c));
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
			image_set_pixel(game->image, x, y, convertRGB(get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.r,
														  get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.g,
														  get_pixel(game->map->tex.we_tex, x_im, y_im).rgba.b));
			y++;
		}
		x++;
	}
	free(form->dim);
	free(form->vector);
	free(form);
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
		len_x += cos((teta / 360.0) * (float) (2 * M_PI)) /
				 200; //en realité on prendra une variable teta passée en parametre pour l'angle
		len_y -= sin((teta / 360.0) * (float) (2 * M_PI)) / 200;
	}
	dist = sqrt((pow(len_y, 2) + pow(len_x, 2)));
	centered_line(game, init_form(init_vector(1, (float) game->image->height / dist),
									   init_vector(x, game->image->height / 2), color));
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
	int len_x;
	int len_y;
	int x;
	int y;

	y = 0;
	len_x = 0;
	len_y = 0;
	while (game->map->map[len_y])
		len_y++;
	while (game->map->map[0][len_x])
		len_x++;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			display_rec(game, init_form(init_vector(15, 15), init_vector(15 * x, 15 * y),
														 game->map->map[y][x] == '1' ? 0xFF54D7 : 0xB9BCC2), image);
			x++;
		}
		y++;
	}
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
	display_rec(game,
			init_form(init_vector(game->image->width, game->image->height / 2), init_vector(0, 0),0xF1F1F1), &game->image);
	display_rec(game, init_form(init_vector(game->image->width, game->image->height / 2),
			init_vector(0, game->image->height / 2), 0x000000), &game->image);
	while (x <= game->image->width && teta >= game->p->yaw - 30)
	{
		display_line(game, x, teta);
		x += 1;
		teta -= 60.0 / game->image->width; //angle de vision * 2
	}
	display_map(game, &game->image); //rajoute la map a l'image
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	mlx_put_image_to_window(game->ptr, game->win, game->map->tex.so_tex->image, 0, 0);

	return (1);

}



