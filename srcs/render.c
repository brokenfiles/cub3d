/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:09:42 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 18:57:33 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				get_type(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x > ft_strlen(map->map[0]) - 1 || y > map->lines - 1)
		return (0);
	return (map->map[y][x]);
}

void		draw_square(t_game *game, t_color c, t_vector v, int size)
{
	int	x;
	int	y;

	y = size * 2 + size * v.y;
	while (y < size * 2 + (size * (v.y + 1)))
	{
		x = size * 2 + size * v.x;
		while (x < size * 2 + (size * (v.x + 1)))
		{
			image_set_pixel(game->image, x, y, clerp(get_pixel(game->image, x, y), c, 0.5f).value);
			x++;
		}
		y++;
	}
}

void			draw_minimap(t_game *game)
{
	t_vector	v;
	int			size;

	size = game->image->width / 10 / ft_strlen(game->map->map[0]);
	v.x = 0;
	while (v.x < ft_strlen(game->map->map[0]))
	{
		v.y = 0;
		while (v.y < game->map->lines)
		{
			if (get_type(game->map, v.x, v.y) == '1')
				draw_square(game, (t_color)0xFFFFFF, v, size);
			v.y++;
		}
		v.x++;
	}
	v.x = game->p->pos->x - 0.5f;
	v.y = game->p->pos->y - 0.5f;
	draw_square(game, (t_color)0xF61A82, v, size);
	v.x += game->p->dir->x;
	v.y += -game->p->dir->y;
	draw_square(game, (t_color)0xFF0000, v, size);
}

int		next_hit(t_game *game, t_ray *ray)
{
	int		hit;

	hit = 0;
	ray->dx = sqrt((ray->y * ray->y) / (ray->x * ray->x) + 1);
	ray->dy = sqrt((ray->x * ray->x) / (ray->y * ray->y) + 1);
	ray->map_x = (int)game->p->pos->x;
	ray->map_y = (int)game->p->pos->y;
	while (hit != '1')
	{
		if (ray->mov_x < ray->mov_y)
		{
			ray->mov_x += ray->dx;
			ray->map_x += (ray->x < 0 ? -1 : 1);
			ray->side = 0;
		}
		else
		{
			ray->mov_y += ray->dy;
			ray->map_y += -(ray->y < 0 ? -1 : 1);
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= game->image->width || ray->map_y >= game->image->height)
			break ;
		//draw_square(game, (t_color)0xFFFFFF, *(init_vector(ray->map_x, ray->map_y)), game->image->width / 10 / ft_strlen(game->map->map[0]));
		hit = get_type(game->map, ray->map_x, ray->map_y);
	}
	return (hit);
}

int				render(t_game *game)
{
	int		hit;
	int		camera;
	t_ray	ray;
	int		x;

	x = 0;
	//while (x < game->image->width)
	//{
		camera = 2.0f * x / game->image->width - 1.0f;
		ray.x = game->p->dir->x + game->p->pos->x * camera;
		ray.y = game->p->dir->y + game->p->pos->y * camera;
		ray.dist = (ray.side ? (ray.map_y - game->p->pos->y + (1 + (ray.y < 0 ? -1 : 1)) / 2) / ray.y :
				(ray.map_x - game->p->pos->x + (1 - (ray.x < 0 ? -1 : 1)) / 2) / ray.x);
		next_hit(game, &ray);
	//	x++;
	//}
}