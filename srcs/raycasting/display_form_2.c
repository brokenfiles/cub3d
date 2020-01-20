/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_form_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:31:04 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:31:04 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_rec_deg(t_game *game, t_form form,
		int t, int color)
{
	t_vector	pos;
	int			r;
	int			g;
	int			b;

	pos.x = form.vector.x;
	while (form.vector.x + form.dim.x > pos.x)
	{
		pos.y = form.vector.y;
		while (form.vector.y + form.dim.y > pos.y)
		{
			r = ft_scale(vec(form.vector.y, form.vector.y + form.dim.y),
					vec(c(form.color).rgba.r, c(color).rgba.r), pos.y);
			g = ft_scale(vec(form.vector.y, form.vector.y + form.dim.y),
					vec(c(form.color).rgba.g, c(color).rgba.g), pos.y);
			b = ft_scale(vec(form.vector.y, form.vector.y + form.dim.y),
					vec(c(form.color).rgba.b, c(color).rgba.b), pos.y);
			set_pixel_transparent(game, vec(pos.x, pos.y),
					c(conv_rgb(r, g, b, 1)), t);
			pos.y++;
		}
		pos.x++;
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
