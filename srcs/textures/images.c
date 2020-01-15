/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:12:38 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	image_set_pixel(t_image *image, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= image->width || y >= image->height))
		*(int *)(image->ptr + ((x + y * image->width) * image->bpp)) = color;
}

int		set_pixel_transparent(t_game *game, t_vector pos, t_color color, float alpha)
{
	t_color	last_pixel;

	last_pixel = get_pixel(game->image, pos.x, pos.y);
	last_pixel.rgba.r = ((alpha * last_pixel.rgba.r) / 255) + (((255 - alpha) * color.rgba.r) / 255);
	last_pixel.rgba.g = ((alpha * last_pixel.rgba.g) / 255) + (((255 - alpha) * color.rgba.g) / 255);
	last_pixel.rgba.b = ((alpha * last_pixel.rgba.b) / 255) + (((255 - alpha) * color.rgba.b) / 255);
	image_set_pixel(game->image, pos.x, pos.y, last_pixel.value);
	return (1);
}

t_image	*del_image(t_game *game, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(game->ptr, img->image);
		free(img);
		img = NULL;
	}
	return (NULL);
}

t_image	*new_image(t_game *game, int w, int h)
{
	t_image		*img;

	if ((img = malloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->image = mlx_new_image(game->ptr, w, h)) == NULL)
		return (del_image(game, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride,
								 &img->endian);
	img->bpp /= 8;
	img->width = w;
	img->height = h;
	return (img);
}

void put_image_to_image(t_image *image, t_image *layer, int x_pos, int y_pos)
{
	int x_l; //TODO : rajouter l'option transparent
	int y_l;
	int value;

	x_l = (x_pos < 0 ? -x_pos : 0);
	y_l = (y_pos < 0 ? -y_pos : 0);
	while (y_l < layer->height && y_pos + y_l < image->height)
	{
		while (x_l < layer->width && x_pos + x_l < image->width)
		{
			value = get_pixel(layer, x_l, y_l).value;
			value != -16777216 ? image_set_pixel(image, x_pos + x_l, y_pos + y_l, value) : 0;
			x_l++;
		}
		x_l = 0;
		y_l++;
	}
}
