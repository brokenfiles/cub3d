/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:12:38 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/17 14:06:19 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	image_set_pixel(t_image *image, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= image->w || y >= image->h))
		*(int *)(image->ptr + ((x + y * image->w) * image->bpp)) = color;
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
	img->w = w;
	img->h = h;
	return (img);
}

void put_image_to_image(t_image *image, t_image *layer, int x_pos, int y_pos, float k)
{
	int	x_l; //TODO : rajouter l'option transparent
	int	y_l;
	int x_scale;
	int y_scale;
	int	value;

	x_l = (x_pos < 0 ? -x_pos : 0);
	y_l = (y_pos < 0 ? -y_pos : 0);
	while (y_l + 1 < layer->h * k && y_pos + y_l < image->h)
	{
		y_scale = ft_scale(vec(0, layer->h * k), vec(0, layer->h), y_l);
		while (x_l + 1 < layer->w * k && x_pos + x_l < image->w)
		{
			x_scale = ft_scale(vec(0, layer->w * k), vec(0, layer->w), x_l);
			value = get_pixel(layer, x_scale, y_scale).value;
			value != -16777216 ? image_set_pixel(image, x_pos + x_l, y_pos + y_l, value) : 0;
			x_l++;
		}
		x_l = 0;
		y_l++;
	}
}
