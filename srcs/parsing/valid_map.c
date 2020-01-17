/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:42:21 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/17 11:30:57 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	remove_spaces(char **line)
{
	int		index;
	int		chars;
	char	*new_str;

	if (!(new_str = (char *)malloc(sizeof(char)
			* (ft_strlen_wc(*line, ' ') + 1))))
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
			return (set_pos(game, vec(x, y), map_line[x]));
		x++;
	}
	return (0);
}

int	check_line(t_game *game, float *last_len, float *pos_found, int index)
{
	char	*line;

	line = game->map->map[index];
	if ((index != 0 && ft_strlen(line) != *last_len) || !ft_stronly(MAP_ONLY,
			line))
		return (0);
	if (index == 0)
		if (!ft_stronly("1", line))
			return (0);
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	(!*pos_found && get_position(game, line, index)) ? *pos_found = 1 :
			*pos_found;
	*last_len = ft_strlen(line);
	return (1);
}

int	valid_map(t_game *game)
{
	int			index;
	t_vector	calc;

	index = 0;
	calc = vec(0, 0);
	while (game->map->map[index])
		if (!check_line(game, &calc.x, &calc.y, index++))
			return (0);
	if (!calc.y || index < 3)
		return (0);
	if (!game->map->spawn_yaw && !game->p.yaw && !game->p.pos.x &&
	!game->p.pos.y)
		return (0);
	game->map->lines = index;
	if (!ft_stronly("1", game->map->map[index - 1]))
		return (1);
	return (1);
}
