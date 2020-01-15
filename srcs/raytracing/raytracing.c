/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/15 19:09:41 by jchotel          ###   ########.fr       */
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
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		ray.dist = (float)sqrt(sq_dist(game->p.pos, hit));
		ray.inter = (ray.wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y);
		if (!print_line(game, form(vec(x, game->dim.y / 2), vec(1, (float)(game->dim.y) / (0.56 * ray.dist)), 0x0), &ray))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		display_sprite(game, ray.sprites, x, angle);
		angle -= (game->angle * 2) / game->dim.x;
		x++;
	}
	free(ray.sprites);
	display_bonus(game, 100);
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	save_image(game);
	return (1);
}
