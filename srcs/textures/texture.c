/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 04:19:00 by pbondoer          #+#    #+#             */
/*   Updated: 2020/01/16 11:09:08 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_color		c(int v)
{
	t_color c;

	c.value = v;
	return (c);
}

t_color		get_pixel(t_image *image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image->w || y >= image->h)
		return ((t_color)0x0);
	return ((t_color)*(int *)(image->ptr + ((x + y * image->w)
											* image->bpp)));
}

/**
 *
 * @param xpm
 * @param game
 * @return
 */
t_image	*xpm_image(char *xpm, t_game *game)
{
	t_image		*img;

	if ((img = malloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->image = mlx_xpm_file_to_image(game->ptr, xpm, &img->w, &img->h)) == NULL)
		return (0);
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride, &img->endian);
	img->bpp /= 8;
	img->w = img->stride / img->bpp;
	img->h = img->stride / img->bpp;
	return (img);
}

/**
 * used to load a texture.
 * @example load_texture(game, &game->map->tex->so_texture, "tex/brick.xmp")
 * @param t_game game
 * @param &t_image image
 * @param char *tex
 * @return t_image *
 */
int	load_tex(t_game *game, t_image **image, char *tex)
{
	t_image		*img;

	if (!tex)
		return (0);
	if ((img = xpm_image(tex, game)) == NULL)
		return (0);
	*image = img;
	return (1);
}

t_image		*get_tex(t_game *game, char c)
{
	if (c == '2')
		return (game->map->tex.sp_tex);
	if (c == 'L')
		return (game->map->tex.li_tex);
	if (c == 'C')
		return (game->map->tex.co_tex);
	return (0);
}