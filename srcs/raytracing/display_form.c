/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/16 10:18:55 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_tri(t_game *game, t_form form)
{
	t_vector	point;
	t_vector	rot;

	point.x = form.vector.x;
	point.y = form.vector.y;
	while (point.x >= form.vector.x - form.dim.x)
	{
		point.y = form.vector.y - (form.vector.x - point.x) / 3;
		while (point.y <= form.vector.y + (form.vector.x - point.x) / 3)
		{
			rot = rotation_matrice(point, vec(form.vector.x, form.vector.y),
					game->p.yaw);
			image_set_pixel(game->image, rot.x, rot.y, form.color);
			point.y++;
		}
		point.x--;
	}
	return (1);
}

int		display_rec(t_game *game, t_form form, t_image **image, int t)
{
	int	y;
	int	x;

	x = form.vector.x;
	while (form.vector.x + form.dim.x > x)
	{
		y = form.vector.y;
		while (form.vector.y + form.dim.y > y)
		{
			set_pixel_transparent(game, vec(x, y), c(form.color), t);
			y++;
		}
		x++;
	}
	return (1);
}

int		display_cir(t_game *game, t_form form, int t)
{
	t_vector	point;
	float		teta;

	point.x = form.vector.x + form.dim.x;
	point.y = form.vector.y;
	teta = 0;
	while (teta < 360.0)
	{
		set_pixel_transparent(game,
				rotation_matrice(point, form.vector, teta),
				c(form.color), t);
		teta++;
	}
	return (1);
}

int		display_cir2(t_game *game, t_form forme, int t)
{
	int	i;

	i = forme.dim.x;
	while (i < forme.dim.y)
	{
		display_cir(game, form(forme.vector, vec(i, 0), forme.color), t);
		i++;
	}
	return (1);
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
	img.x = ft_scale(0.0, 1.0, 0.0, tex->w, ray->inter);
	calc.x = form.vector.y - (form.dim.y / 2);
	calc.y = form.vector.y + (form.dim.y / 2);
	screen.y = 0;
	while (game->dim.y > screen.y)
	{
		if (screen.y > form.vector.y - (form.dim.y / 2) &&
		screen.y <= form.vector.y + (form.dim.y / 2))
		{
			img.y = ft_scale((int)calc.x, (int)calc.y, 0, tex->h, screen.y);
			ray->dist = 255 / (255 / (ray->dist));
//			color = convert_rgb(get_pixel(tex, img.x, img.y).rgba.r - ray->dist, get_pixel(tex, img.x, img.y).rgba.g - ray->dist, get_pixel(tex, img.x, img.y).rgba.b - ray->dist);
			color = get_pixel(tex, img.x, img.y).value & 0xFFFFFF;
		}
		else
			color = (screen.y >= game->dim.y / 2) ?
					game->map->floor_color : game->map->sky_color;
		image_set_pixel(game->image, form.vector.x, screen.y++, color);
	}
	return (1);
}
