/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2019/11/28 17:59:33 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	display_rectangle(t_data *data, t_rectangle *rectangle)
{
	int	y;
	int	x;

	x = rectangle->vector->x;
	while (rectangle->vector->x + rectangle->dimension->width - x > 0)
	{
		y = rectangle->vector->y;
		while (rectangle->vector->y + rectangle->dimension->height - y > 0)
		{
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, rectangle->color);
			y++;
		}
		x++;
	}
	free(rectangle->dimension);
	free(rectangle->vector);
	free(rectangle);
	return (1);
}

int	display_triangle(t_data *data, t_triangle *triangle)
{
	int	y;
	int	x;

	x = triangle->vector1->x;
	y = triangle->vector1->y;
	while(x < triangle->vector2->x)
	{
		y = triangle->vector1->y;
		while (((float)(triangle->vector1->y - y)/(float)(triangle->vector1->y - triangle->vector2->y)) <= ((float)(x - triangle->vector1->x)/(float)(triangle->vector2->x - triangle->vector1->x)))
		{
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, triangle->color);
			y--;
		}
		x++;
	}
	free(triangle->vector1);
	free(triangle->vector2);
	free(triangle);
	return (1);
}

int	display_map(t_data *data, t_map *map, t_player *player)
{
	int	index;
	int	index2;

	index = 0;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	while (map->map[index])
	{
		index2 = 0;
		while (map->map[index][index2])
		{
			if (player->location.y == index && player->location.x == index2)
				display_rectangle(data, init_rectangle(init_dimension(20, 20), init_vector(20 * index, 20 * index2), 0x4749FF));
			else
				display_rectangle(data, init_rectangle(init_dimension(20, 20), init_vector(20 * index, 20 * index2), map->map[index][index2] == '1' ? 0xFF54D7 : 0xB9BCC2));
			index2++;
		}
		index++;
	}
	return (1);
}

int	update_map(t_data *data, t_map *map, t_player *player)
{
	int	index;
	int	index2;

	index = 0;
	display_rectangle(data, init_rectangle(init_dimension(20, 20), init_vector(20 * player->location.y, 20 * player->location.x), 0x4749FF));
	return (1);
}