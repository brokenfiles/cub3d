/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 19:16:33 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_map(t_game *game, t_image **image)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			display_rec_trans(game, form(
					vec(game->dim.x / MAP_SIZE * x, game->dim.x / MAP_SIZE * y),
					vec(game->dim.x / MAP_SIZE, game->dim.x / MAP_SIZE),
					ft_strchr("1DH", game->map->map[y][x]) ?
					WALL_COLOR : VOID_COLOR), image);
			if (ft_strchr("2LCU", game->map->map[y][x]))
				display_cir2(game, form(vec(game->dim.x / MAP_SIZE * (x + 0.5f),
				game->dim.x / MAP_SIZE * (y + 0.5f)), vec(0, 5), 0xFF2B12));
			x++;
		}
		y++;
	}
	return (1);
}
