/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/18 14:03:36 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int				render(t_game *game)
{
	t_vector	hit;
	t_ray		ray;
	float		angle;
	int			x;

	x = 0;
	angle = game->angle;
	ray.sprites = malloc(sizeof(struct s_sprite) * 10);
	while (angle > -game->angle)
	{
		init_ray(&ray, (float)game->p.yaw + angle);
		hit = next_hit(game, &ray);
		if (hit.x == 0 && hit.y == 0)
			return (quit(EXIT_FAILURE, MSG_RENDERING_ERROR));
		ray.dist = (float)sqrt(sq_dist(game->p.pos, hit));
		ray.inter = (ray.wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y);
		if (!print_line(game, form(vec(x, game->p.vision), vec(0, ((float)(game->dim.y) / (0.56 * ray.dist))), 0x0), &ray))
			return (quit(EXIT_FAILURE, MSG_RENDERING_ERROR));
		display_sprite(game, &ray, x);
		angle -= (game->angle * 2) / game->dim.x;
		x++;
	}
	free(ray.sprites);
	display_bonus(game, BONUS_OPACITY);
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	save_image(game);
	return (1);
}
