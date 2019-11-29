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

void display_pixel(t_data *data, t_vector *vector, int color)
{
    mlx_pixel_put(data->mlx_ptr, data->mlx_win, vector->x, vector->y, color);
}

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
/*
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
}*/


int    display_tri(t_data *data, t_player *player, t_tri *triangle)
{
    int    y;
    int    x;
    
    x = triangle->vector->x;
    y = triangle->vector->y;
    while(x >= triangle->vector->x - triangle->height)
    {
        y = triangle->vector->y - (triangle->vector->x - x) / 3;
        while (y <= triangle->vector->y + (triangle->vector->x - x) / 3)
        {
            display_pixel(data, rotation_matrice(player, x, y), triangle->color);
            y++;
        }
        x--;
    }
    free(triangle->vector);
    free(triangle);
    return (1);
}



int	display_map(t_data *data, t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (player->location.y == y && player->location.x == x)
				display_rectangle(data, init_rectangle(init_dimension(20, 20), init_vector(20 * x, 20 * y), 0x4749FF));
            else
				display_rectangle(data, init_rectangle(init_dimension(20, 20), init_vector(20 * x, 20 * y), map->map[y][x] == '1' ? 0xFF54D7 : 0xB9BCC2));
			x++;
		}
		y++;
	}
	return (1);
}

int centered_line(t_data *data, t_rectangle *rectangle)
{
    int    y;
    int    x;
    
    x = rectangle->vector->x;
    while (rectangle->vector->x + rectangle->dimension->width - x > 0)
    {
        y = rectangle->vector->y - (rectangle->dimension->height / 2);
        
        while (rectangle->vector->y + (rectangle->dimension->height / 2) > y)
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

int display_full_range(t_game *game)
{
    int x;
    float teta;
    
    x = (game->data->width / 2) - 1200;
    teta = game->player->location.yaw + 20;
    while (x <= (game->data->width / 2) + 1200)
    {
        display_line(game, x, teta);
        x +=4;
        teta -= 0.1;
    }
    return (1);
    
}


int display_line(t_game *game, int x, float teta)
{
    float len_x;
    float len_y;
    float height;
    
    len_x = 0;
    len_y = 0;
    while (game->map->map[(int)(game->player->location.y + len_y)][(int)(game->player->location.x + len_x)] != '1')
    {
        len_x += cos((teta / 360.0) * (float)(2 * M_PI)) / 20; //en realité on prendra une variable teta passée en parametre pour l'angle
        len_y -= sin((teta/ 360.0) * (float)(2 * M_PI)) / 20;
    }
    //printf("dist : %f\n", pow(len_x, 2) + pow(len_y, 2));
    height = (float)game->data->height *  (29 / (58 + (pow(len_x, 2) + pow(len_y, 2))));
    //printf("height : %f\n", height);
    //display_rectangle(game->data, init_rectangle(init_dimension(4, game->data->height / 4), init_vector(x, game->data->height / 4), 0xFF49FF)); //ciel;
    //display_rectangle(game->data, init_rectangle(init_dimension(4, game->data->height / 4), init_vector(x, game->data->height / 2), 0x47FFFF)); //sol;
    centered_line(game->data, init_rectangle(init_dimension(4, 20 * sqrt(height)), init_vector(x, game->data->height / 2), 0xFFFFFF)); //faire deux autres lignes de mêmes epaisseurs qui comletent celle-ci pour faire le ciel et le sol
    return (1);
}

int	update_map(t_data *data, t_map *map, t_player *player)
{//passer un pointeur de fonction en arg (soit un direction_change soit une/deux nouvelles pour key_up et down)
    //on pourra donc effacer le curseur, faire les modifications sur sa structure puis afficher le cursuer dans chaque cas de handle_key
	int	index;
	int	index2;

	index = 0;
	display_rectangle(data, init_rectangle(init_dimension(20, 20), init_vector(20 * player->location.x, 20 * player->location.y), 0x4749FF));
	return (1);
}
