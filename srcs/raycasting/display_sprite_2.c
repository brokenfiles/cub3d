/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprite_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:13:45 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 13:28:11 by llaurent         ###   ########.fr       */
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
	t_sprite	sprite;

	sprite.pos = hit;
	sprite.wall = *wall;
	sprite.defined = 1;
	sprite.tex = get_tex(game, game->map->map[(int)hit.y][(int)hit.x]);
	return (sprite);
}

float		calc_inter(t_ray *r, t_sprite *sp)
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

float		calc_inter2(t_ray *r, t_sprite *sp)
{
	float		inter;
	t_vector	v;

	v = vec(sp->pos.x - (int)sp->pos.x, sp->pos.y - (int)sp->pos.y);
	if (r->alpha <= M_PI_2)
		return (sp->wall % 2 == 0 ? r->cos + v.x * r->sin : v.y * r->cos);
	else if (r->alpha > M_PI_2 && r->alpha <= M_PI)
		return (sp->wall % 2 == 0 ? r->sin * v.x : r->sin - (1 - v.y) * r->cos);
	else if (r->alpha > M_PI && r->alpha <= 3 * M_PI_2)
		return (sp->wall % 2 == 0 ? 1 + r->sin * v.x :
		1 + (r->sin + v.y * r->cos));
	else
		return (sp->wall % 2 == 0 ? r->sin * (v.x - 1) :
		-r->sin + v.y * r->cos);
}
