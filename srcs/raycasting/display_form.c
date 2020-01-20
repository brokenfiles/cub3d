/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_form.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:31:00 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:31:00 by llaurent         ###   ########.fr       */
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

void	print_line(t_game *game, t_form f, t_ray *ray)
{
	t_vector	screen;
	t_vector	img;
	t_vector	calc;
	t_image		*tex;
	t_color		c;

	set_texture(game, ray, &tex);
	img.x = ft_scale2(0.0, 1.0, tex->w, ray->inter);
	calc = vec(f.vector.y - (f.dim.y / 2), f.vector.y + (f.dim.y / 2));
	screen.y = 0;
	while (game->dim.y > screen.y)
	{
		if (screen.y > f.vector.y - (f.dim.y / 2) &&
		screen.y + 1 < f.vector.y + (f.dim.y / 2))
		{
			img.y = ft_scale2((int)calc.x, (int)calc.y, tex->h, screen.y);
			c = get_pixel(tex, img.x, img.y);
			c.value = ray->dist >= 3 ? conv_rgb(c.rgba.r, c.rgba.g, c.rgba.b,
					(1 - ray->dist * 2 / 255)) : c.value;
		}
		else
			c.value = (screen.y >= game->p.vision) ?
					game->map->floor_color : game->map->sky_color;
		image_set_pixel(game->image, f.vector.x, screen.y++, c.value);
	}
}
