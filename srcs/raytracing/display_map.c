/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 20:14:11 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		display_map(t_game *game, t_image **image, int t)
{
	int	x;
	int	y;
	int	c;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			c = ft_strchr("1DH", game->map->map[y][x]) ? WALL_COLOR : VOID_COLOR;
			display_rec(game, form(
					vec(game->dim.x / MAP_SIZE * x, game->dim.x / MAP_SIZE * y),
					vec(game->dim.x / MAP_SIZE, game->dim.x / MAP_SIZE),
					c), image, t);
			if (ft_strchr("2LCU", game->map->map[y][x]))
			{
				c = (game->map->map[y][x] == 'C' ? 0xDD22DD : 0xFF2B12);
				c = (game->map->map[y][x] == '2' ? 0x0000FF : c);
				c = (game->map->map[y][x] == 'U' ? 0x00FF00 : c);
				display_cir2(game, form(vec(game->dim.x / MAP_SIZE * (x + 0.5f),
				game->dim.x / MAP_SIZE * (y + 0.5f)), vec(0, 5), c), 240);
			}
			x++;
		}
		y++;
	}
	return (1);
}
