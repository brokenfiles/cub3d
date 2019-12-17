/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 02:38:25 by jchotel          ###   ########.fr       */
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



int display_cir(t_game *game, t_form *form)
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

float sq_dist(t_vector *origin, t_vector *point)
{
	return (pow(point->x - origin->x, 2) + pow(point->y - origin->y, 2));
}

t_vector next_inter(t_vector *p, t_vector vec, float teta, int *wall, t_game *game)
{
	float c;
	float alpha;
	t_vector x;
	t_vector y;
	t_vector res; //variable to delete

	alpha = (teta / 360) * (float)(2 * M_PI);
	c = vec.y + tan(alpha) * vec.x;
	x.x = (int) vec.x + (cos(alpha) > 0 ? 1 : -1); //(vec.x = (int)vec.x && cos(alpha) > 0 ? 0 : -1) + (cos(alpha) > 0 ? 1 : -1);
	x.y = -tan(alpha) * (float) x.x + c;
	mlx_pixel_put(game->ptr, game->win, x.x*game->map->tex.size, x.y*game->map->tex.size, 0x0000FF);
	mlx_pixel_put(game->ptr, game->win, x.x*game->map->tex.size + 1, x.y*game->map->tex.size, 0x0000FF);
	mlx_pixel_put(game->ptr, game->win, x.x*game->map->tex.size , x.y*game->map->tex.size + 1, 0x0000FF);
	mlx_pixel_put(game->ptr, game->win, x.x*game->map->tex.size + 1, x.y*game->map->tex.size + 1, 0x0000FF);
	y.y = (int) vec.y + (sin(alpha) > 0 ? -1 : 1);//(vec.y = (int)vec.y && sin(alpha) > 0 ? -1 : 0) + (sin(alpha) > 0 ? 0 : 1);
	y.x = (y.y - c) / -tan(alpha);
	mlx_pixel_put(game->ptr, game->win, y.x*game->map->tex.size, y.y*game->map->tex.size, 0x00FF00);
	mlx_pixel_put(game->ptr, game->win, y.x*game->map->tex.size + 1, y.y*game->map->tex.size, 0x00FF00);
	mlx_pixel_put(game->ptr, game->win, y.x*game->map->tex.size , y.y*game->map->tex.size + 1, 0x00FF00);
	mlx_pixel_put(game->ptr, game->win, y.x*game->map->tex.size + 1, y.y*game->map->tex.size + 1, 0x00FF00);
	res = (sq_dist(p, &y) > sq_dist(p, &x) ? x : y); //ligne a mettre dans le return
	printf ("%s avec x.x=%f x.y=%f y.x=%f y.y=%f\n", sq_dist(p, &y) > sq_dist(p, &x) ? "bleu plus court" : "vert plus court", x.x, x.y, y.x, y.y);
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
	t_vector res;
	float alpha;

	res = next_inter(p, *p, teta, wall, game);
	alpha = (teta / 360) * (float)(2 * M_PI);
	while (map->map[(int)(res.y)][(int)(res.x+ ((cos(alpha) > 0 && *wall = 1)? 0 : -1))] != '1')
	{
		printf("%d\n", *wall);
		res = next_inter(p, res, teta, wall, game);
	}
	return (res);
}

//t_vector test_hit2(t_vector *p, float teta, int *wall, t_game *game)
//{
//	float alpha;
//	t_vector delta;
//	t_vector move;
//	t_vector hit;
//
//	alpha = (teta / 360) * (float)(2 * M_PI);
//	if (cos(alpha) == 0 || sin(alpha) == 0)
//	{
//		printf("we are fucked\n");
//		return (*init_vector(0, 0));
//	}
//	delta.x = cos(alpha);
//	delta.y = -sin(alpha);
//	move.x =  ((int)p->x - p->x) * delta.x;//(cos(alpha) > 0 ? 1 : 0)) * delta.x;
//	move.y =  ((int)p->y - p->y + (-sin(alpha) > 0 ? 1 : 0)) * delta.y;
//	while (game->map->map[(int)(p->y + move.y)][(int)(p->x + move.x)] == '0')
//	{
//		if (fabs(move.x) < fabs(move.y))
//			move.x += delta.x;
//		else
//			move.y += delta.y;
//	}
//	hit.x = (int)(p->x + move.x);
//	hit.y = (int)p->y; //(int)(p->y + move.y);
//	return (hit);
//}










//t_vector test_hit(t_vector *p, float teta, int *wall, t_game *game)
//{
//	float alpha;
//	float rayDirX;
//	float rayDirY;
//	int stepX;
//	int stepY;
//	float sideDistX;
//	float sideDistY;
//	float deltaDistX;
//	float deltaDistY;
//	int mapX;
//	int mapY;
//	int side;
//	t_vector res;
//
//	alpha = (teta / 360) * (float)(2 * M_PI);
//	rayDirX = cos(alpha);
//	rayDirY = cos(alpha);
//	deltaDistX = fabs(1 / rayDirX);
//	deltaDistY = fabs(1 / rayDirY);
//	mapX = (int)p->x;
//	mapY = (int)p->y;
//	if (rayDirX < 0)
//	{
//		stepX = -1;
//		sideDistX = (p->x - mapX) * deltaDistX;
//	}
//	else
//	{
//		stepX = 1;
//		sideDistX = (mapX + 1.0 - p->x) * deltaDistX;
//	}
//	if (rayDirY < 0)
//	{
//		stepY = -1;
//		sideDistY = (p->y - mapY) * deltaDistY;
//	}
//	else
//	{
//		stepY = 1;
//		sideDistY = (mapY + 1.0 - p->y) * deltaDistY;
//	}
//
//	while (game->map->map[mapY][mapX] == '0')
//	{
//		//jump to next map square, OR in x-direction, OR in y-direction
//		if (sideDistX < sideDistY)
//		{
//			sideDistX += deltaDistX;
//			mapX += stepX;
//			side = 0;
//		}
//		else
//		{
//			sideDistY += deltaDistY;
//			mapY += stepY;
//			side = 1;
//		}
//	}
//}




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
	//mlx_put_image_to_window(game->ptr, game->win, game->map->tex.so_tex->image, 0, 0);

	return (1);

}



