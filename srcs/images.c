/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:12:38 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 13:15:16 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	put_int_in_char(unsigned char *begin, int val)
{
	begin[0] = (unsigned char)(val);
	begin[1] = (unsigned char)(val >> 8);
	begin[2] = (unsigned char)(val >> 16);
	begin[3] = (unsigned char)(val >> 24);
}

static int	write_header(int fd, int size, t_game *game)
{
	int				index;
	unsigned char	header[54];

	index = 0;
	while (index < 54)
		header[index++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	put_int_in_char(header + 2, size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	put_int_in_char(header + 18, game->image->width);
	put_int_in_char(header + 22, game->image->height);
	header[27] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

static int	write_data(int file, t_game *game, int step)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					x;
	int					y;
	int					color;

	y = game->image->height;
	while (y > 0)
	{
		x = 0;
		while (x < game->image->width)
		{
			color = convertRGB(get_pixel(game->image, x, y).rgba.r, get_pixel(game->image, x, y).rgba.g, get_pixel(game->image, x, y).rgba.b);
			if (write(file, &color, 3) < 0)
				return (0);
			if (step > 0 && write(file, &zero, step) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int		save_bitmap(t_game *game, char *name)
{
	int			size;
	int			file;
	int			step;

	ft_putstr("Saving screenshot...\n");
	step = (4 - ((int)game->image->width * 3) % 4) % 4;
	size = 54 + (3 * ((int)game->image->width + step) * (int)game->image->height);
	if ((file = open(name, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR)) < 0)
		return (0);
	if (!write_header(file, size, game))
		return (0);
	if (!write_data(file, game, step))
		return (0);
	close(file);
	ft_putstr(name);
	ft_putstr(" saved.\n");
	return (1);
}
