/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/17 13:26:59 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		clear_sprites(t_sprite *sprites, int n)
{
	while (n-- > 0)
		sprites[n + 1] = init_sprite();
}

t_sprite	set_sprite(t_vector hit, int *wall, t_game *game)
{
	t_sprite sprite;

	sprite.pos = hit;
	sprite.wall = *wall;
	sprite.defined = 1;
	sprite.tex = get_tex(game, game->map->map[(int)hit.y][(int)hit.x]);
	return (sprite);
}

float	calc_inter(t_ray *r, t_sprite *sp)
{
	float		inter;
	t_vector	k;
	t_vector	v;

	v = vec(sp->pos.x - (int)sp->pos.x, sp->pos.y - (int)sp->pos.y);
	k = vec(r->sin * r->sin, r->cos * r->cos);
	if (r->alpha > 3 * M_PI_2 && r->alpha <= 2 * M_PI)
		return (sp->wall % 2 == 0 ? (1 - v.x) * k.x : 1 - (1 - v.y) * k.y);
	else if (r->alpha > M_PI_2 && r->alpha <= M_PI)
		return (sp->wall % 2 == 0 ? v.x * k.x : 1 - (v.y) * k.y);
	else if (r->alpha > M_PI && r->alpha <= 3 * M_PI_2)
		return (sp->wall % 2 == 0 ? 1 - (v.x) * k.x : (1 - v.y) * k.y);
	else
		return (sp->wall % 2 == 0 ? 1 - (1 - v.x) * k.x : (v.y) * k.y);
}

float	calc_inter2(t_ray *r, t_sprite *sp)
{
	float		inter;
	//t_vector	k;
	t_vector	v;

	v = vec(sp->pos.x - (int)sp->pos.x, sp->pos.y - (int)sp->pos.y);
	//k = vec(r->sin * r->sin, r->cos * r->cos);
	if (sp->wall % 2 == 0) //x_inter
		return (0);
	else //y_inter
		return (r->sin + v.y * r->cos);
}


int		print_sprite(t_game *game, t_form form, float inter, float dist, t_image *tex)
{
	t_vector	screen;
	t_vector	im;
	t_vector	calc;
	t_color		c;

	screen.x = form.vector.x;
	im.x = ft_scale(0.0, 1.0, 0.0, tex->w, inter);
	calc.x = form.vector.y - (form.dim.x / 2);
	calc.y = form.vector.y + (form.dim.x / 2);
	screen.y = form.vector.y - (form.dim.y / 2);
	while (screen.y <= form.vector.y + (form.dim.y / 2))
	{
		im.y = ft_scale((int)calc.x, (int)calc.y, 0, tex->h, screen.y);
		c = get_pixel(tex, im.x, im.y);
		c.value = convert_rgb(c.rgba.r, c.rgba.g, c.rgba.b, (1 - dist * 15 / 255));
		if (c.value != 0x000000)
			image_set_pixel(game->image, screen.x, screen.y, c.value);
		screen.y++;
	}
	return (1);
}

int		display_sprite(t_game *game, t_ray *r, int x)
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
				inter, dist, sprite->tex))
				return (quit(EXIT_FAILURE, MSG_RENDERING_ERROR));
		}
		index--;
	}
	return (1);
}
