/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 04:19:00 by pbondoer          #+#    #+#             */
/*   Updated: 2019/12/16 13:05:46 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_color		c(int v)
{
	t_color c;

	c.value = v;
	return (c);
}
//UTILITE ??? 
int			ft_lerpi(int first, int second, double p)
{
	if (first == second)
		return (first);
    return ((int)((double)first + (second - first) * p));
}

t_color		clerp(t_color c1, t_color c2, double p)
{
	t_color c;

	if (c1.value == c2.value)
		return (c1);
	p = (p < 0.0f ? 0.0f : p); 
	p = (p > 1.0f ? 1.0f : p);
	c.rgba.r = (char)ft_lerpi((int)c1.rgba.r, (int)c2.rgba.r, p);
	c.rgba.g = (char)ft_lerpi((int)c1.rgba.g, (int)c2.rgba.g, p);
	c.rgba.b = (char)ft_lerpi((int)c1.rgba.b, (int)c2.rgba.b, p);
	c.rgba.a = (char)0x00;
	return (c);
}

t_color		get_pixel(t_image *image, int x, int y)
{
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ((t_color)0x0);
	return ((t_color)*(int *)(image->ptr + ((x + y * image->width)
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
	if ((img->image = mlx_xpm_file_to_image(game->ptr, xpm, &img->width, &img->height)) == NULL)
		return (0);
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride, &img->endian);
	img->bpp /= 8;
	img->width = img->stride / img->bpp;
	img->height = img->stride / img->bpp;
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
t_image	*load_tex(t_game *game, t_image **image, char *tex)
{
	t_image		*img;

	if ((img = xpm_image(tex, game)) == NULL)
	{
		//free_tex(mlx);
		return (0);
	}
	*image = img;
	return (img);
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
