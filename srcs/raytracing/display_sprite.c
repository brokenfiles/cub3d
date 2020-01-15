/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 19:02:41 by jchotel          ###   ########.fr       */
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

int			display_sprite(t_game *game, t_sprite *sprites, int x, float angle)
{
	float teta;
	float dist;
	float x_inter;
	t_sprite *sprite;
	int 	index;

	index = 4;
	while (index >= 0)
	{
		sprite = &sprites[index];
		if (sprite->defined == 1)
		{
			dist = sqrt(sq_dist(game->p.pos, vec((int)sprite->pos.x, (int)sprite->pos.y)));
			teta = (((float)game->p.yaw + angle)/ 360.0) * (float)(2 * M_PI);
			teta = teta < 0 ? 2 * M_PI + teta : teta;
			if (teta > 3 * M_PI/2 && teta <= 2 * M_PI)
				x_inter = sprite->wall % 2 == 0 ? (1 - sprite->pos.x + (int)sprite->pos.x) * sin(teta) * sin(teta) : 1 - (1 - sprite->pos.y + (int)sprite->pos.y) * cos(teta) * cos(teta);
			else if (teta > M_PI/2 && teta <= M_PI)
				x_inter = sprite->wall % 2 == 0 ? (sprite->pos.x - (int)sprite->pos.x) * sin(teta) * sin(teta) : 1 - (sprite->pos.y - (int)sprite->pos.y) * cos(teta) * cos(teta);
			else if (teta > M_PI && teta <= 3 * M_PI / 2)
				x_inter = sprite->wall % 2 == 0 ? 1 - (sprite->pos.x - (int)sprite->pos.x) * sin(teta) * sin(teta) : (1 - sprite->pos.y + (int)sprite->pos.y) * cos(teta) * cos(teta);
			else
				x_inter = sprite->wall % 2 == 0 ? 1 - (1 - sprite->pos.x + (int)sprite->pos.x) * sin(teta) * sin(teta) : (sprite->pos.y - (int)sprite->pos.y) * cos(teta) * cos(teta);
			if (!print_sprite(game, form(vec(x, game->dim.y / 2), vec((float)(game->dim.y / 0.56) / dist, (float)(game->dim.y / 0.56) / dist), 0x0), x_inter, dist, sprite->tex))
				return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		}
		index--;
	}
	return (1);
}
