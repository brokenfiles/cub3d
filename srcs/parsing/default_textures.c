/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:23:53 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/14 13:43:32 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_default_textures(t_game *game)
{
	if (!(load_tex(game, &game->map->tex.lu_tex, LU_DEFAULT_TEX)))
		return (0);
	if (!(load_tex(game, &game->map->tex.do_tex, DO_DEFAULT_TEX)))
		return (0);
	if (!(load_tex(game, &game->map->tex.li_tex, LI_DEFAULT_TEX)))
		return (0);
	if (!(load_tex(game, &game->map->tex.co_tex, CO_DEFAULT_TEX)))
		return (0);
	return (1);
}