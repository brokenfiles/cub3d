/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:12:38 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/18 13:44:38 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	image_set_pixel(t_image *image, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= image->w || y >= image->h))
		*(int *)(image->ptr + ((x + y * image->w) * image->bpp)) = color;
}

int		set_pixel_transparent(t_game *game, t_vector pos, t_color color,
		float alpha)
{
	t_color	last_pixel;

	last_pixel = get_pixel(game->image, pos.x, pos.y);
	last_pixel.rgba.r = ((alpha * last_pixel.rgba.r) / 255) + (((255 - alpha)
			* color.rgba.r) / 255);
	last_pixel.rgba.g = ((alpha * last_pixel.rgba.g) / 255) + (((255 - alpha)
			* color.rgba.g) / 255);
	last_pixel.rgba.b = ((alpha * last_pixel.rgba.b) / 255) + (((255 - alpha)
			* color.rgba.b) / 255);
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
	t_image	*img;

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

void	put_image_to_image(t_image *image, t_image *layer, t_vector pos,
		float k)
{
	t_vector	v_l;
	t_vector	v_sc;
	int			value;

	v_l.x = (pos.x < 0 ? -pos.x : 0);
	v_l.y = (pos.y < 0 ? -pos.y : 0);
	while (v_l.y + 1 < layer->h * k && pos.y + v_l.y < image->h)
	{
		v_sc.y = ft_scale(vec(0, layer->h * k), vec(0, layer->h), v_l.y);
		while (v_l.x + 1 < layer->w * k && pos.x + v_l.x < image->w)
		{
			v_sc.x = ft_scale(vec(0, layer->w * k), vec(0, layer->w), v_l.x);
			value = get_pixel(layer, v_sc.x, v_sc.y).value;
			value != -16777216 ? image_set_pixel(image, pos.x + v_l.x,
					pos.y + v_l.y, value) : 0;
			v_l.x++;
		}
		v_l.x = 0;
		v_l.y++;
	}
}
