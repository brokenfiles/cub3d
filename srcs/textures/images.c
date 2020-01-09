/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:12:38 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/09 16:19:22 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	image_set_pixel(t_image *image, int x, int y, int color)
{
	if (!(x < 0 || y < 0 || x >= image->width || y >= image->height))
		*(int *)(image->ptr + ((x + y * image->width) * image->bpp)) = color;
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
