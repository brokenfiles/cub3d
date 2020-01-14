/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:23:53 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/14 13:41:23 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_default_textures(t_game *game)
{
	if (!(load_tex(game, &game->map->tex.lu_tex, "textures/jesus.XPM")))
		return (0);
	if (!(load_tex(game, &game->map->tex.do_tex, "textures/tropical.XPM")))
		return (0);
	if (!(load_tex(game, &game->map->tex.li_tex, "textures/minecraft/heart.xpm")))
		return (0);
	if (!(load_tex(game, &game->map->tex.co_tex, "textures/planet_rose.XPM")))
		return (0);
	return (1);
}