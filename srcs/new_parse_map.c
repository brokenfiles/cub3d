/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:10:57 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/06 17:18:26 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

char	get_key(char *str)
{
	while (*(str - 1))
		str--;
	return (*(str + 1));
}

int	is_structure_full(t_game *game)
{
	if (!game->image->width || !game->map->tex.sky_color ||
	!game->map->tex.floor_color || !game->map->tex.ea_tex ||
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
		return (line + ft_strlen(key));
	return (NULL);
}

int	fill_data(t_game *game, char *line)
{
	char	*tmp;
	int		index;
	int		colors[4];

	index = 0;
	if ((tmp = get_val(line, "R ")))
	{
		if (!(game->image->width = ft_atoi(tmp)))
			return (0);
		tmp += get_int_len(game->image->width);
		if (!(game->image->height = ft_atoi(tmp)))
			return (0);
	}
	if (((tmp = get_val(line, "C ")) && !(colors[3] = 0)) ||
	((tmp = get_val(line, "F ")) && (colors[3] = 1)))
	{
		while (index++ < 3)
		{
			colors[index - 1] = ft_atoi(tmp);
			if (!(tmp = to_next_char(tmp, ',')))
				break;
		}
		if (index < 3)
			return (0);
		if (colors[3] == 1)
			game->map->floor_color = convertRGB(colors[0], colors[1], colors[2]);
		else
			game->map->sky_color = convertRGB(colors[0], colors[1], colors[2]);
	}

	return (1);
}

int	parse_map(t_game *game, char *map_name)
{
	int		fd;
	char	*line;

	if ((fd = open(map_name, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		if (!is_structure_full(game))
		{
			if (!fill_data(game, line))
				return (0);
		}
		else
			printf("la map\n");
//		free(*line);
	}
	printf("w: %d, h: %d\n", game->image->width, game->image->height);
	printf("floor: %d\n", game->map->floor_color);
	printf("sky: %d\n", game->map->sky_color);
	if (!is_structure_full(game))
		return (0);
	return (1);
}