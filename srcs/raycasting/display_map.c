/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:31:07 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:31:07 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		choose_color(char o)
{
	int	color;

	color = (o == 'C' ? 0xDD22DD : 0xFF2B12);
	color = (o == '2' ? 0x0000FF : color);
	c(o == 'U' ? 0x00FF00 : color);
	return (color);
}

void	display_map(t_game *game, t_image **image, int t)
{
	t_vector	p;
	int			co;

	p = vec(0, 0);
	while (game->map->map[(int)p.y])
	{
		p.x = 0;
		while (game->map->map[(int)p.y][(int)p.x])
		{
			co = ft_strchr("1DH", game->map->map[(int)p.y][(int)p.x]) ?
					WALL_COLOR : VOID_COLOR;
			display_rec(game, form(vec(game->dim.x / MAP_SIZE * p.x
					, game->dim.x / MAP_SIZE * p.y), vec(game->dim.x / MAP_SIZE,
							game->dim.x / MAP_SIZE), co), image, t);
			if (ft_strchr("2LCU", game->map->map[(int)p.y][(int)p.x]))
			{
				co = choose_color(game->map->map[(int)p.y][(int)p.x]);
				display_cir2(game, form(vec(game->dim.x / MAP_SIZE *
				(p.x + 0.5f),
				game->dim.x / MAP_SIZE * (p.y + 0.5f)), vec(0, 5), co), 240);
			}
			p.x++;
		}
		p.y++;
	}
}
