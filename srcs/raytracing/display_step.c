/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:52:13 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/16 19:15:36 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	put_image_screen(t_game *game, t_image *image, t_vector pos, float k)
{
//	printf("k : %f, image->w : %d, image->w * k : %f, image->w / k : %f\n", k, image->w, (float)image->w * k, (float)image->w / k);
	//display_rec(game, form(vec(pos.x - (float)image->w * k / 2, pos.y - (float)image->h * k / 4), vec(2, 2), 0xFAFAFA), &game->image, 0);
	put_image_to_image(game->image, image, pos.x - (float)image->w * k / 2, pos.y - (float)image->h * k / 2, k);
	return (1);
}

int	display_step(t_game *game)
{
	if (game->step == STEP_START)
	{
		//0xFFEF0E jaune
		//0xFFD390 beige
		display_rec_deg(game, form(vec(0, 0), vec(game->dim.x, game->dim.y), 0x04003F), &game->image, 0, 0x872984);
		put_image_screen(game, game->map->tex.logo_tex, vec(game->dim.x / 2, game->dim.y / 2), 0.4f * (float)game->dim.x / (float)game->dim.y);
		put_image_screen(game, game->map->tex.m_enter_tex, vec(game->dim.x / 2, 90.0f * (float)game->dim.y / 100.0f), (1.2f) * (float)game->dim.x / (float)game->dim.y);
		put_image_screen(game, game->map->tex.m_n_tex, vec(game->dim.x / 2, 29 * (float)game->dim.y / 30), (0.5f) * (float)game->dim.x / (float)game->dim.y);
	}
	else if (game->step == STEP_END)
	{
		display_rec_deg(game, form(vec(0, 0), vec(game->dim.x, game->dim.y), 0x872984), &game->image, 0, 0x04003F);
		put_image_screen(game, game->map->tex.m_g_o_tex, vec(game->dim.x / 2, (float)game->dim.y / 2), (5.0f) * (float)game->dim.x / (float)game->dim.y);
		put_image_screen(game, game->map->tex.m_n_tex, vec(game->dim.x / 2, 29 * (float)game->dim.y / 30), (0.5f) * (float)game->dim.x / (float)game->dim.y);
	}
	else
		return (0);
	return (1);
}