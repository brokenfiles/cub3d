/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:04:42 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 11:16:38 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_nbr_length(unsigned int nb)
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

char	*get_value(char **splitted, char *key)
{
	int		index;
	char	*tmp;

	index = 0;
	if (!key || !splitted || !*splitted)
		return (0);
	while (splitted[index])
	{
		if ((tmp = ft_strnstr(splitted[index], key, ft_strlen(key))))
			return (splitted[index] + ft_strlen(key));
		index++;
	}
	return (NULL);
}

int	get_position(char **map, t_player *p)
{
	int	index;
	int	index2;

	index = 0;
	while (map[index])
	{
		index2 = 0;
		while (map[index][index2])
		{
			if (ft_strchr("WENS", map[index][index2]))
			{
				p->pos->y = index;
				p->pos->x = index2;
				p->yaw = 90.0;
				p->yaw = (map[index][index2] == 'S' ? 270.0 : p->yaw);
				p->yaw = (map[index][index2] == 'E' ? 360.0 : p->yaw);
				p->yaw = (map[index][index2] == 'W' ? 180.0 : p->yaw);
				return (0);
			}
			index2++;
		}
		index++;
	}
	return (0);
}

int		check_value(char **splitted, char *search)
{
	int	index;

	index = 0;
	if (!search || !splitted || !*splitted)
		return (0);
	while (splitted[index])
	{
		if (ft_strnstr(splitted[index], search, ft_strlen(search)))
			return (1);
		index++;
	}
	return (0);
}

int		get_map_line(char **splitted)
{
	int		index;
	int		counter;

	index = 0;
	counter = 0;
	while (splitted[index])
	{
		if (ft_stronly("120WENS", splitted[index]))
			counter++;
		index++;
	}
	return (counter);
}

int	free_map(char **map, int counter)
{
	while (counter > 0)
	{
		free(map[counter]);
		counter--;
	}
	free(map);
	return (0);
}

int	get_only_map(char **splitted, t_map *map)
{
	int		index;
	int		counter;
	int		lines;

	index = 0;
	counter = 0;
	if ((lines = get_map_line(splitted)) == -1 || lines < 3)
		return (0);
	map->lines = lines;
	if (!(map->map = (char **)malloc(sizeof(char *) * (lines + 1))))
		return (0);
	while (splitted[index])
	{
		if (ft_stronly("120WENS", splitted[index]))
		{
			if (!(map->map[counter] = ft_strdup(splitted[index])))
				return (free_map(map->map, counter));
			counter++;
		}
		index++;
	}
	map->map[counter] = 0;
	return (1);
}

char	*get_content(char *map_name)
{
	int		fd;
	char	buffer[64 + 1];
	char	*content;
	int		index;
	int		r;

	index = 0;
	if (!(content = (char *)malloc(sizeof(char))))
		return (NULL);
	content[0] = '\0';
	if ((fd = open(map_name, O_RDONLY)) == -1)
		return (NULL);
	while ((r = read(fd, buffer, 64)) > 0)
	{
		buffer[r] = 0;
		content = ft_strjoin(content, buffer);
	}
	if (close(fd) == -1 || ft_strlen(content) < 1)
		return (NULL);
	return (content);
}

int	checks(char **splitted)
{
	if (!check_value(splitted, "NO ") || !check_value(splitted, "SO "))
		return (0);
	if (!check_value(splitted, "WE ") || !check_value(splitted, "EA "))
		return (0);
	if (!check_value(splitted, "F ") || !check_value(splitted, "C "))
		return (0);
	return (1);
}

int	fill_values(char **splitted, t_game *game)
{
	char	*res;

	if (!(res = get_value(splitted, "R ")))
		return (0);
	if (!(game->image->width = ft_atoi(res)))
		return (0);
	if (!res[get_nbr_length(game->image->width)])
		return (0);
	res += get_nbr_length(game->image->width);
	if (!(game->image->height = ft_atoi(res)))
		return (0);
	if (game->image->width < MIN_WIDTH || game->image->height < MIN_HEIGHT)
		return (0);
	if (!(load_tex(game, &game->map->tex.no_tex, get_value(splitted, "NO "))) ||
		!(load_tex(game, &game->map->tex.so_tex, get_value(splitted, "SO "))) ||
		!(load_tex(game, &game->map->tex.we_tex, get_value(splitted, "WE "))) ||
		!(load_tex(game, &game->map->tex.ea_tex, get_value(splitted, "EA "))) ||
		!(load_tex(game, &game->map->tex.sp_tex, get_value(splitted, "S "))) ||
		!(game->map->tex.floor_color = get_value(splitted, "F ")) ||
		!(game->map->tex.sky_color = get_value(splitted, "C ")))
		return (0);
	game->map->tex.wall_color = 0xFF0000;
	game->map->tex.void_color = 0x000000;
	game->map->tex.p_color = 0x4749FF;
	game->map->tex.size = 10;
	get_position(game->map->map, game->p);
	return (1);
}

int	fill_map(char *map_name, t_game *game)
{
	char	**splitted;
	char	*content;
	int		index;

	index = 0;
	if (!(content = get_content(map_name)))
		return (0);
	if (!(splitted = ft_split(content, "\n")))
		return (0);
	if (!checks(splitted))
		return (0);
	if (!get_only_map(splitted, game->map))
		return (0);
	if (!ft_stronly("1", game->map->map[0]) || !ft_stronly("1", game->map->map[game->map->lines - 1]))
		return (0);
	while (game->map->map[index])
	{
		if (game->map->map[index][0] != '1' || game->map->map[index][ft_strlen(game->map->map[index]) - 1] != '1')
			return (0);
		index++;
	}
	if (!fill_values(splitted, game))
		return (0);
	//printf("res : width %d height %d\n", data->width, data->height);
	return (1);
}
