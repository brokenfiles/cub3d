/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:42:21 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_strlen_wc(char *str, char c)
{
	int	counter;

	counter = 0;
	while (*str)
		if (*(str++) != c)
			counter++;
	return (counter);
}

int	remove_spaces(char **line)
{
	int		index;
	int		chars;
	char	*new_str;

	if (!(new_str = (char *)malloc(sizeof(char) * (ft_strlen_wc(*line, ' ') + 1))))
		return (0);
	index = 0;
	chars = 0;
	while ((*line)[index])
	{
		if ((*line)[index] != ' ')
		{
			new_str[chars] = (*line)[index];
			chars++;
		}
		index++;
	}
	new_str[chars] = 0;
	*line = new_str;
	free(*line);
	return (1);
}

int	set_pos(t_game *game, t_vector vector, char id)
{
	game->p.pos = vector;
	game->map->spawn = vector;
	if (id == 'W')
		game->p.yaw = WEST;
	if (id == 'E')
		game->p.yaw = EAST;
	if (id == 'N')
		game->p.yaw = NORTH;
	if (id == 'S')
		game->p.yaw = SOUTH;
	game->map->spawn_yaw = game->p.yaw;
	return (1);
}

int	get_position(t_game *game, char *map_line, int y)
{
	int	x;

	x = 0;
	while (map_line[x])
	{
		if (ft_strchr(POS_ONLY, map_line[x]))
			return (set_pos(game, vector(x, y), map_line[x]));
		x++;
	}
	return (0);
}

int	valid_map(t_game *game)
{
	int		index;
	int		last_len;
	int		pos_found;
	t_map	*map;

	index = 0;
	last_len = 0;
	pos_found = 0;
	map = game->map;
	while (map->map[index])
	{
		if ((index != 0 && ft_strlen(map->map[index]) != last_len) || !ft_stronly(MAP_ONLY, map->map[index]))
			return (0);
		if (index == 0)
			if (!ft_stronly("1", map->map[index]))
				return (0);
		if (map->map[index][0] != '1' || map->map[index][ft_strlen(map->map[index]) - 1] != '1')
			return (0);
		(!pos_found && get_position(game, map->map[index], index)) ? pos_found = 1 : pos_found;
		last_len = ft_strlen(map->map[index]);
		index++;
	}
	if (!pos_found || index < 3)
		return (0);
	if (!map->spawn_yaw && !game->p.yaw && !game->p.pos.x && !game->p.pos.y)
		return (0);
	map->lines = index;
	if (!ft_stronly("1", map->map[index - 1]))
		return (1);
	return (1);
}
