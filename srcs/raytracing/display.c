/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/14 16:04:57 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
t_ray		init_ray(float teta)
{
	t_ray ray;

	ray.a = (teta / 360.0) * (float)(2 * M_PI);
	ray.c = cos(ray.a);
	ray.s = sin(ray.a);
	ray.t = tan(ray.a);
	return (ray);
}

int		set_wall(t_vector res, t_vector x, t_vector y, t_ray *ray)
{
	if (res.x == x.x && res.y == x.y && ray->c > 0)
		ray->wall = 1;
	else if (res.x == x.x && res.y == x.y)
		ray->wall = 3;
	else if (ray->s > 0)
		ray->wall = 2;
	else
		ray->wall = 4;
	return (ray->wall);
}



t_vector	next_inter(t_vector p, t_vector vec, float teta, int *wall, t_game *game)
{
	float		c;
	t_vector	x;
	t_vector	y;
	t_vector	res;
	t_ray		r;

	r = init_ray(teta);
	c = vec.y + r.t * vec.x;
	x.x = (int)vec.x + (vec.x == (int)vec.x && r.c < 0 ? -1 : 0) + (r.c > 0 ? 1 : 0);
	x.y = -r.t * (float)x.x + c;
	y.y = (int)vec.y + (vec.y == (int)vec.y && r.s > 0 ? -1 : 0) + (r.s > 0 ? 0 : 1);
	y.x = (y.y - c) / -r.t;
	res = (sq_dist(p, y) > sq_dist(p, x) ? x : y);
	//image_set_pixel(game->image, res.x*game->map->tex.size, res.y*game->map->tex.size, 0xACACAC);
	set_wall(res, x, y, &r);
	*wall = r.wall;

	return (res);
}

t_vector	next_block(t_vector res, t_vector p)
{
	t_vector hit;

	hit.x = res.x - (p.x > res.x && res.x == (int)res.x ? 0.0001 : 0);
	hit.y = res.y - (p.y > res.y && res.y == (int)res.y ? 0.0001 : 0);
	return (hit);
}

t_vector	next_hit(t_map *map, t_vector p, float teta, int *wall, t_game *game, t_sprite *sprites, int x)
{
	t_vector	res;
	int			number;
	t_sprite	sprite;
	t_vector	hit;
	int			i;

	number = 0;
	i = 0;
	if (!map->map[(int)p.y][(int)p.x])
		return (res);
	res = next_inter(p, p, teta, wall, game);
	if (res.x == 0 && res.y == 0)
		return (res);
	hit = next_block(res, p);
	clear_sprites(sprites, 9);
	while (map->map[(int)hit.y][(int)hit.x] && (!ft_strchr("DUH1", map->map[(int)hit.y][(int)hit.x])))
	{
		number++;
		if (number > 1000)
			quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR_429);
		res = next_inter(p, res, teta, wall, game);
		hit = next_block(res, p);
		if (map->map[(int)hit.y][(int)hit.x] == 'D' && *wall % 2 != 0)
			*wall = 5;
		else if (map->map[(int)hit.y][(int)hit.x] == 'D')
			*wall = 6;
		if (map->map[(int)hit.y][(int)hit.x] == 'U' && *wall % 2 != 0)
			*wall = 7;
		else if (map->map[(int)hit.y][(int)hit.x] == 'U')
			*wall = 8;
		if (ft_strchr("2LC", map->map[(int)hit.y][(int)hit.x]) && i < 9)
			sprites[++i] = set_sprite(hit, wall, game);
	}
	return (res);
}

int				render(t_game *game)
{
	t_vector hit;
	t_sprite sprite;
	t_sprite *sprites;
	float angle;
	float angle_copy; //DEGAGE dans game
	int x;
	int wall; //DEGAGE dans t_ray
	float dist; //DEGAGE dans t_ray

	x = 0;
	angle = game->image->width * (float)(1.0f / (game->image->height / 17)); //pas besoin de le recalculer a chaque nouveau render TODO : mettre cette valeur dans une structure
	angle_copy = angle;
	sprites = malloc(sizeof(struct s_sprite) * 10);
	while (angle > -angle_copy)
	{
		clear_sprites(sprites, 9);
		sprite.pos = vector(-1, -1);
		hit = next_hit(game->map, game->p.pos, (float)game->p.yaw + angle, &wall, game, sprites, x);
		if (hit.x == 0 && hit.y == 0)
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		dist = (float)sqrt(sq_dist(game->p.pos, hit));
		if (!test_line(game, form(vector(x, game->image->height / 2), vector(1, (float)(game->image->height / 0.56) / dist), 0x0), (wall % 2 == 0 ? hit.x - (int)hit.x : hit.y - (int)hit.y), wall, dist))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
		display_sprite(game, sprites, x, angle);
		angle -= (angle_copy * 2) / game->image->width;
		x++;
	}
	free(sprites);
	display_bonus(game);
	mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	//mlx_put_image_to_window(game->ptr, game->win, game->map->tex.nbrs[0]->image, 0, 0); //PERMET D'AFFICHER UNE IMAGE
	save_image(game);
	return (1);
}
