/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:40:07 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/10 16:03:22 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			color = get_pixel(game->image, x, y).value;
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

int save_image(t_game *game)
{
	if (game->save_first_image)
	{
		game->save_first_image = 0;
		if (!save_bitmap(game, "screenshot.bmp"))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	}
	return (1);
}