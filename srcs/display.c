/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/03 16:37:38 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * display pixel but DEPRECIATED!
 * @deprecated
 * @param t_data data
 * @param t_vector vector
 * @param int color
 */
void display_pixel(t_data *data, t_vector *vector, int color)
{
	mlx_pixel_put(data->mlx_ptr, data->mlx_win, vector->x, vector->y, color);
}

/**
 * used to display a rectangle but with images
 * //TODO: define pixel color using the textures
 * @apprecieted
 * @param t_game game
 * @param t_rectangle rectangle
 * @return int (1 = success, 0 = fail)
 */
int display_rectangle_image(t_game *game, t_rectangle *rectangle, t_image **image)
{
	int y;
	int x;

	x = rectangle->vector->x;
	while (rectangle->vector->x + rectangle->dimension->width - x > 0)
	{
		y = rectangle->vector->y;
		while (rectangle->vector->y + rectangle->dimension->height - y > 0)
		{
			if (rectangle->color == -1)
			{
				image_set_pixel(*image, x, y, clerp(c(0x0), get_pixel(game->map->textures.no_texture, x % 30, y % 30), x).value);
			}
			else if (rectangle->color == -2)
			{
				image_set_pixel(*image, x, y, clerp(c(0x0), get_pixel(game->map->textures.so_texture, x % 30, y % 30), 1.0f).value);
			}
			else
			{
				image_set_pixel(*image, x, y, rectangle->color);
			}
			y++;
		}
		x++;
	}
	free(rectangle->dimension);
	free(rectangle->vector);
	free(rectangle);
	return (1);
}

/**
 * put a rectangle in pixel (does not using images)
 * @deprecated because of pixel put
 * @param t_data data
 * @param t_rectangle rectangle
 * @return int (1 = success, 0 = fail)
 */
int display_rectangle(t_data *data, t_rectangle *rectangle)
{
	int y;
	int x;

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

/**
 * used to display a triangle
 * TODO: change pixelput to images
 * @deprecated for now
 * @param t_data data
 * @param t_player player
 * @param t_triangle triangle
 * @return int (1 = success, 0 = fail)
 */
int display_tri(t_data *data, t_player *player, t_tri *triangle)
{
	int y;
	int x;

	x = triangle->vector->x;
	y = triangle->vector->y;
	while (x >= triangle->vector->x - triangle->height)
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

/**
 * used to display the map
 * @param t_data data
 * @param t_map map
 * @param t_player player
 * @return int (1 = success, 0 = fail)
 */
int	display_map(t_game *game, t_image **image)
{
	int		len_x;
	int		len_y;
	int		x;
	int		y;

	y = 0;
	len_x = 0;
	len_y = 0;
	while (game->map->map[len_y])
		len_y++;
	while (game->map->map[0][len_x])
		len_x++;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			display_rectangle_image(game, init_rectangle(init_dimension(15, 15), init_vector(15 * x, 15 * y), game->map->map[y][x] == '1' ? 0xFF54D7 : 0xB9BCC2), image);
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * display a centered line
 * //TODO: define pixel color using the textures
 * @param t_game game
 * @param t_rectangle rectangle
 * @return int (1 = success, 0 = fail)
 */
int centered_line(t_game *game, t_rectangle *rectangle)
{
	int y;
	int x;

	x = rectangle->vector->x;
	//printf("0x%d, r: %d, g: %d, b:%d\n", get_pixel(game->map->textures.we_texture, x % 36, y % 36).value,
	//		get_pixel(game->map->textures.we_texture, x % 36, y % 36).rgba.r,
	//		get_pixel(game->map->textures.we_texture, x % 36, y % 36).rgba.g,
	//		get_pixel(game->map->textures.we_texture, x % 36, y % 36).rgba.b);
	while (rectangle->vector->x + rectangle->dimension->width - x > 0)
	{
		y = rectangle->vector->y - (rectangle->dimension->height / 2);
		while (rectangle->vector->y + (rectangle->dimension->height / 2) > y)
		{
			image_set_pixel(game->image, x, y, rectangle->color);
			y++;
		}
		x++;
	}
	free(rectangle->dimension);
	free(rectangle->vector);
	free(rectangle);
	return (1);
}

//game->image = new_image(game, 100, 100);
//image_set_pixel(game->image, 5, 5, 0xFFFFFF);
//mlx_put_image_to_window(game->data->mlx_ptr, game->data->mlx_win, game->image->image, 100, 100);

/**
 * display the render
 * @param t_game game
 * @return int (1 = success, 0 = fail)
 */
int display_full_range(t_game *game)
{
	int x;
	float teta;

	x = 0;
	teta = game->player->location.yaw + 20; //angle de vision
	game->image = new_image(game, game->data->width, game->data->height);
	display_rectangle_image(game, init_rectangle(init_dimension(game->data->width, game->data->height / 2), init_vector(0, 0), 0xFAFAFA), &game->image);
	display_rectangle_image(game, init_rectangle(init_dimension(game->data->width, game->data->height / 2), init_vector(0, game->data->height / 2), 0x000000), &game->image);
	while (x <= 1920 && teta >= game->player->location.yaw - 20)
	{
		display_line(game, x, teta);
		x += 1;
		teta -= 40.0 / game->data->width; //angle de vision * 2
	}
	display_map(game, &game->image); //rajoute la map a l'image
	mlx_put_image_to_window(game->data->mlx_ptr, game->data->mlx_win, game->image->image, 0, 0);
	mlx_put_image_to_window(game->data->mlx_ptr, game->data->mlx_win, game->map->textures.so_texture, 0, 0);

	return (1);

}

int convertRGB(int R, int G, int B)
{
    R = (R > 255 ? 255 : R);
    G = (G > 255 ? 255 : G);
    B = (B > 255 ? 255 : B);
    R = (R < 0 ? 0 : R);
    G = (G < 0 ? 0 : G);
    B = (B < 0 ? 0 : B);
    return (65536 * R + 256 * G + B);
}


/**
 * used to display a line
 * @param t_game game
 * @param x
 * @param teta (orientation of the player)
 * @return int (1 = success, 0 = fail)
 */
int display_line(t_game *game, int x, float teta)
{
	float len_x;
	float len_y;
	float dist;

    len_x = 0;
    len_y = 0;
    
	while (game->map->map[(int) (game->player->location.y + len_y)][(int) (game->player->location.x + len_x)] != '1')
	{
		len_x += cos((teta / 360.0) * (float) (2 * M_PI)) / 200; //en realité on prendra une variable teta passée en parametre pour l'angle
		len_y -= sin((teta / 360.0) * (float) (2 * M_PI)) / 200;
	}
	dist = sqrt((pow(len_y, 2) + pow(len_x, 2)));
	centered_line(game, init_rectangle(init_dimension(1, (float) game->data->height / dist), init_vector(x, game->data->height / 2), convertRGB(255,255,0)));
	return (1);
}











/**
 * used to update the map
 * @param t_data data
 * @param t_map map
 * @param t_player player
 * @return int (1 = success, 0 = fail)
 */
int update_map(t_data *data, t_map *map, t_player *player)
{//passer un pointeur de fonction en arg (soit un direction_change soit une/deux nouvelles pour key_up et down)
	//on pourra donc effacer le curseur, faire les modifications sur sa structure puis afficher le cursuer dans chaque cas de handle_key
	int index;
	int index2;

	index = 0;
	display_rectangle(data, init_rectangle(init_dimension(20, 20),
										   init_vector(20 * player->location.x, 20 * player->location.y), 0xFF54D7));
	return (1);
}
