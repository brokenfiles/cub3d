/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:12:14 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		set_wall(t_ray *ray, t_vector x, t_vector y)
{
	ray->wall = (ray->pos.x == x.x && ray->pos.y == x.y && ray->cos > 0 ? 1 : 4);
	ray->wall = (ray->pos.x == x.x && ray->pos.y == x.y && ray->cos < 0 ? 3 : ray->wall);
	ray->wall = (ray->pos.x == y.x && ray->pos.y == y.y && ray->sin > 0 ? 2 : ray->wall);
	return (ray->wall);
}

int		set_doors(t_ray *ray, char c)
{
	if (c == 'D' && ray->wall % 2 != 0)
		ray->wall = 5;
	else if (c == 'D')
		ray->wall = 6;
	if (c == 'U' && ray->wall % 2 != 0)
		ray->wall = 7;
	else if (c == 'U')
		ray->wall = 8;
	else
		return (0);
	return (1);
}

t_vector	next_block(t_vector res, t_vector p)
{
	t_vector hit;

	hit.x = res.x - (p.x > res.x && res.x == (int)res.x ? 0.0001 : 0);
	hit.y = res.y - (p.y > res.y && res.y == (int)res.y ? 0.0001 : 0);
	return (hit);
}

t_vector	next_inter(t_vector p, t_vector vec, t_ray *ray)
{
	float		c;
	t_vector	x;
	t_vector	y;

	c = vec.y + ray->tan * vec.x;
	x.x = (int)vec.x + (vec.x == (int)vec.x && ray->cos < 0 ? -1 : 0) + (ray->cos > 0 ? 1 : 0);
	x.y = -ray->tan * (float)x.x + c;
	y.y = (int)vec.y + (vec.y == (int)vec.y && ray->sin > 0 ? -1 : 0) + (ray->sin > 0 ? 0 : 1);
	y.x = (y.y - c) / -ray->tan;
	ray->pos = (sq_dist(p, y) > sq_dist(p, x) ? x : y);
	//image_set_pixel(game->image, res.x*game->map->tex.size, res.y*game->map->tex.size, 0xACACAC);
	ray->wall = set_wall(ray, x, y);
	return (ray->pos);
}

t_vector	next_hit(t_game *game, t_ray *ray)
{
	t_vector	hit;
	int			number;
	char		c;

	number = 0;
	ray->sprite_num = 0;
	ray->pos = next_inter(game->p.pos, game->p.pos, ray);
	hit = next_block(ray->pos, game->p.pos);
	c = game->map->map[(int)hit.y][(int)hit.x];
	while (!(ray->pos.x == 0 && ray->pos.y == 0)&& c && (!ft_strchr("DUH1", c)))
	{
		if (++number > 1000)
			quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR_429);
		ray->pos = next_inter(game->p.pos, ray->pos, ray);
		hit = next_block(ray->pos, game->p.pos);
		c = game->map->map[(int)hit.y][(int)hit.x];
		set_doors(ray, c);
		if (ft_strchr("2LC", c) && ray->sprite_num < 9)
			ray->sprites[++ray->sprite_num] = set_sprite(hit, &ray->wall, game);
	}
	return (ray->pos);
}

int				render(t_game *game)
{
	t_vector	hit;
	t_ray		ray;
	float		angle;
	int			x;

	x = 0;
	angle = game->angle; //pas besoin de le recalculer a chaque nouveau render TODO : mettre cette valeur dans une structure
	ray.sprites = malloc(sizeof(struct s_sprite) * 10);
	while (angle > -game->angle)
	{
		init_ray(&ray, (float)game->p.yaw + angle);
		hit = next_hit(game, &ray);
		if (hit.x == 0 && hit.y == 0)
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		ray.dist = (float)sqrt(sq_dist(game->p.pos, hit));
		ray.inter = (ray.wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y);
		if (!print_line(game, form(vector(x, game->dim.y / 2), vector(1, (float)(game->dim.y) / (0.56 * ray.dist)), 0x0), &ray))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		display_sprite(game, ray.sprites, x, angle);
		angle -= (game->angle * 2) / game->dim.x;
		x++;
	}
	free(ray.sprites);
	display_bonus(game);
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	save_image(game);
	return (1);
}
