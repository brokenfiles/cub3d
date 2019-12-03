/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/03 15:06:03 by llaurent         ###   ########.fr       */
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
			//display_rectangle(game->data, init_rectangle(init_dimension(20, 20), init_vector(20 * x, 20 * y), game->map->map[y][x] == '1' ? 0xFF54D7 : 0xB9BCC2));
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
			//image_set_pixel(game->image, x, y, clerp(c(0x0), get_pixel(game->map->textures.we_texture, x % 36, y % 36), 1.0f).value);
			image_set_pixel(game->image, x, y, 0xF2F2F2);
			//mlx_pixel_put(data->mlx_ptr, game->data->mlx_win, x, y, (rectangle->vector->y + (rectangle->dimension->height / 2) > y + 1) ? rectangle->color : 0x6FFF43);
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

	x = (game->data->width / 2) - 1200;
	teta = game->player->location.yaw + 20;
	game->image = new_image(game, game->data->width, game->data->height);
	display_rectangle_image(game, init_rectangle(init_dimension(1920, game->data->height / 2), init_vector(0, 0), 0xFAFAFA), &game->image);
	display_rectangle_image(game, init_rectangle(init_dimension(1920, game->data->height / 2), init_vector(0, game->data->height / 2), 0xAFAFAF), &game->image);
	while (x <= (game->data->width / 2) + 1200)
	{
		//printf("x : %d, teta : %d\n", x, (int)teta);
		//image_set_pixel(game->image, 5, 5, 0xFFFFFF);
		display_line(game, x, teta);
		x += 4;
		teta -= 0.1;
	}
	display_map(game, &game->image);
	mlx_put_image_to_window(game->data->mlx_ptr, game->data->mlx_win, game->image->image, 0, 0);
	//mlx_put_image_to_window(game->data->mlx_ptr, game->data->mlx_win, game->map->textures.so_texture, 0, 0);
	return (1);

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
	float height;
	//void	*image;

	len_x = 0;
	len_y = 0;
	while (game->map->map[(int) (game->player->location.y + len_y)][(int) (game->player->location.x + len_x)] != '1')
	{
		len_x += cos((teta / 360.0) * (float) (2 * M_PI)) /
				 20; //en realité on prendra une variable teta passée en parametre pour l'angle
		len_y -= sin((teta / 360.0) * (float) (2 * M_PI)) / 20;
	}
	//printf("dist : %f\n", pow(len_x, 2) + pow(len_y, 2));
	height = (float) game->data->height / (pow(len_x, 2) + pow(len_y, 2));
	//printf("height : %f\n", height);
	//display_rectangle(game->data, init_rectangle(init_dimension(4, game->data->height / 4), init_vector(x, game->data->height / 4), 0x4EFFFF)); //ciel;
	//display_rectangle(game->data, init_rectangle(init_dimension(4, game->data->height / 4), init_vector(x, game->data->height / 2), 0xB9BCC2)); //sol;
	centered_line(game, init_rectangle(init_dimension(4, 20 * sqrt(height)), init_vector(x, game->data->height / 2), 0xFF54D7)); //faire deux autres lignes de mêmes epaisseurs qui comletent celle-ci pour faire le ciel et le sol
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
