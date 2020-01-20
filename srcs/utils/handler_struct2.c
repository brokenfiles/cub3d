/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_struct2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:31:37 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:31:37 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int			init_tex(t_game *game)
{
	game->map->tex.ea_tex = NULL;
	game->map->tex.we_tex = NULL;
	game->map->tex.so_tex = NULL;
	game->map->tex.no_tex = NULL;
	game->map->tex.sp_tex = NULL;
	return (1);
}

t_sprite	init_sprite(void)
{
	t_sprite	sprite;

	sprite.defined = 0;
	sprite.pos.x = -1;
	sprite.pos.y = -1;
	sprite.wall = -1;
	return (sprite);
}

t_vector	vec(float x, float y)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_form		form(t_vector vector, t_vector dim, int color)
{
	t_form	form;

	form.dim = dim;
	form.vector = vector;
	form.color = color;
	return (form);
}
