
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

#include "../../includes/cub3d.h"

int display_tri(t_game *game, t_form form)
{
	t_vector point;
	t_vector rot;

	point.x = form.vector.x;
	point.y = form.vector.y;
	while (point.x >= form.vector.x - form.dim.x)
	{
		point.y = form.vector.y - (form.vector.x - point.x) / 3;
		while (point.y <= form.vector.y + (form.vector.x - point.x) / 3)
		{
			rot = rotation_matrice(point, vector(form.vector.x, form.vector.y), game->p.yaw);
			image_set_pixel(game->image, rot.x, rot.y, form.color);
			point.y++;
		}
		point.x--;
	}
	return (1);
}

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

int display_rec_trans(t_game *game, t_form form, t_image **image) //Est-ce qu'on peut pas avoir une seule fonction display_rec qui permet de set la transparence ?
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

int display_cir(t_game *game, t_form form)
{
	t_vector point;
	float teta;
	point.x = form.vector.x + form.dim.x;
	point.y = form.vector.y;
	teta = 0;
	while (teta < 360.0)
	{
		image_set_pixel(game->image, rotation_matrice(point, form.vector, teta).x, rotation_matrice(point, form.vector, teta).y, form.color);
		teta++;
	}
	return (1);
}
int display_cir2(t_game *game, t_form forme)
{
	int i;
	i = forme.dim.x;
	while (i < forme.dim.y)
	{
		display_cir(game, form(forme.vector, vector(i, 0), forme.color));
		i++;
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

int		set_texture(t_game *game, t_ray *ray, t_image **tex)
{
	if (ray->wall == 1)
		*tex = game->map->tex.we_tex;
	if (ray->wall == 2)
		*tex = game->map->tex.no_tex;
	if (ray->wall == 3)
		*tex = game->map->tex.ea_tex;
	if (ray->wall == 4)
		*tex = game->map->tex.so_tex;
	if (ray->wall == 5 || ray->wall == 6)
		*tex = game->map->tex.do_tex;
	if (ray->wall == 7 || ray->wall == 8)
		*tex = game->map->tex.lu_tex;
	return (1);
}

int		print_line(t_game *game, t_form form, t_ray *ray)
{
	t_vector	screen;
	t_vector	img;
	t_vector	calc;
	t_image		*tex;
	int			color;

	set_texture(game, ray, &tex);
	img.x = ft_scale(0.0, 1.0, 0.0, tex->width, ray->inter);
	calc.x = form.vector.y - (form.dim.y / 2);
	calc.y = form.vector.y + (form.dim.y / 2);
	screen.y = 0;
	while (game->dim.y > screen.y)
	{
		if (screen.y > form.vector.y - (form.dim.y / 2) &&
		screen.y <= form.vector.y + (form.dim.y / 2))
		{
			img.y = ft_scale((int) calc.x, (int) calc.y, 0, tex->height, screen.y);
			ray->dist = 255 / (255 / (ray->dist));
			color = get_pixel(tex, img.x, img.y).value & 0xFFFFFF;
//				color = convert_rgb(get_pixel(tex, img.x, img.y).rgba.r - ray->dist, get_pixel(tex, img.x, img.y).rgba.g - ray->dist, get_pixel(tex, img.x, img.y).rgba.b - ray->dist);
		}
		else
			color = (screen.y >= game->dim.y / 2) ?
					game->map->floor_color : game->map->sky_color;
		image_set_pixel(game->image, form.vector.x, screen.y++, color);
	}
	return (1);
}

int		print_sprite(t_game *game, t_form form, float x_inter, float dist, t_image *tex)
{
	t_vector	screen;
	t_vector	im;
	t_vector	calc;
	int		color;

	screen.x = form.vector.x;
	im.x = ft_scale(0.0, 1.0, 0.0, tex->width, x_inter);
	calc.x = form.vector.y - (form.dim.x / 2);
	calc.y = form.vector.y + (form.dim.x / 2);
	screen.y = form.vector.y - (form.dim.y / 2);
	while (screen.y <= form.vector.y + (form.dim.y / 2))
	{
		im.y = ft_scale((int)calc.x, (int)calc.y, 0, tex->height, screen.y);
		color = get_pixel(tex, im.x, im.y).value & 0xFFFFFF;
		if (color != 0x000000)
			image_set_pixel(game->image, screen.x, screen.y, color);
		screen.y++;
	}
	return (1);
}
