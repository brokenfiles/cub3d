/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/20 13:26:43 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 ** dat.x = inter
 ** dat.y = dist
*/

int	print_sprite(t_game *game, t_form form, t_vector dat, t_image *tex)
{
	t_vector	screen;
	t_vector	im;
	t_vector	calc;
	t_color		c;

	screen.x = form.vector.x;
	form.dim.x = (game->dim.x > form.dim.x ? form.dim.x : game->dim.x);
	form.dim.y = form.dim.x;
	im.x = ft_scale2(0.0, 1.0, tex->w, dat.x);
	calc.x = form.vector.y - (form.dim.x / 2);
	calc.y = form.vector.y + (form.dim.x / 2);
	screen.y = form.vector.y - (form.dim.y / 2);
	while (screen.y <= form.vector.y + (form.dim.y / 2))
	{
		im.y = ft_scale2((int)calc.x, (int)calc.y, tex->h, screen.y);
		c = get_pixel(tex, im.x, im.y);
		c.value = conv_rgb(c.rgba.r, c.rgba.g, c.rgba.b, (1 - dat.y * 2 / 255));
		if (c.value != 0x000000)
			image_set_pixel(game->image, screen.x, screen.y, c.value);
		screen.y++;
	}
	return (1);
}

int	display_sprite(t_game *game, t_ray *r, int x)
{
	float		dist;
	float		inter;
	t_sprite	*sprite;
	int			index;

	index = 4;
	while (index >= 0)
	{
		sprite = &r->sprites[index];
		if (sprite->defined == 1)
		{
			dist = sqrt(sq_dist(game->p.pos, vec((int)sprite->pos.x,
					(int)sprite->pos.y)));
			inter = calc_inter2(r, sprite);
			if (!print_sprite(game, form(vec(x, game->p.vision),
				vec((float)(game->dim.y / 0.56) / dist,
				(float)(game->dim.y / 0.56) / dist), 0x0),
				vec(inter, dist), sprite->tex))
				return (quit(EXIT_FAILURE, MSG_RENDERING_ERROR));
		}
		index--;
	}
	return (1);
}
