/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:19:43 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 11:16:07 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		get_int_len(unsigned int nb)
{
	unsigned int	index;

	index = 0;
	while (nb >= 10)
	{
		nb /= 10;
		index++;
	}
	return (index + 1);
}

int		is_structure_full(t_game *game)
{
	if (!game->image->width || !game->map->sky_color ||
		!game->map->floor_color || !game->map->tex.ea_tex ||
		!game->map->tex.no_tex || !game->map->tex.so_tex ||
		!game->map->tex.we_tex || !game->image->height)
		return (0);
	return (1);
}

char	*to_next_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c && *(str + 1))
			return (str + 1);
		str++;
	}
	return (NULL);
}

char	*get_val(char *line, char *key)
{
	char	*tmp;

	if (!key || !line)
		return (0);
	if ((tmp = ft_strnstr(line, key, ft_strlen(key))))
	{
		line = line + ft_strlen(key);
		while (*line == ' ')
			line++;
		return (line);
	}
	return (NULL);
}

int		get_resolution(t_game *game, char *line)
{
	char	*tmp;

	if (game->level > 0)
		return (1);
	if (!(tmp = get_val(line, "R ")))
		return (0);
	if (!(game->image->width = ft_atoi(tmp)))
		return (0);
	tmp += get_int_len(game->image->width);
	if (!(game->image->height = ft_atoi(tmp)))
		return (0);
	if (game->image->height >= MAX_HEIGHT)
		game->image->height = MAX_HEIGHT;
	if (game->image->width >= MAX_WIDTH)
		game->image->width = MAX_WIDTH;
	if (game->image->height <= MIN_HEIGHT)
		game->image->height = MIN_HEIGHT;
	if (game->image->width <= MIN_WIDTH)
		game->image->width = MIN_WIDTH;
	return (1);
}
