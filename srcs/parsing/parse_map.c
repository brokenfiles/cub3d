/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:10:57 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/08 17:36:51 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			game->map->floor_color = convert_rgb(colors[0], colors[1], colors[2]);
		else
			game->map->sky_color = convert_rgb(colors[0], colors[1], colors[2]);
	}
	load_tex(game, &game->map->tex.no_tex, get_val(line, "NO "));
	load_tex(game, &game->map->tex.so_tex, get_val(line, "SO "));
	load_tex(game, &game->map->tex.we_tex, get_val(line, "WE "));
	load_tex(game, &game->map->tex.ea_tex, get_val(line, "EA "));
	load_tex(game, &game->map->tex.sp_tex, get_val(line, "S "));
	return (1);
}

int	get_resolution(t_game *game, char *line)
{
	char	*tmp;

	if (!(tmp = get_val(line, "R ")))
		return (0);
	if (!(game->image->width = ft_atoi(tmp)))
		return (0);
	tmp += get_int_len(game->image->width);
	if (!(game->image->height = ft_atoi(tmp)))
		return (0);
	return (1);
}

int	get_texture(t_game *game, char *line, char *key)
{
	int	all_was_good;

//	all_was_good = 1;
//	if (ft_strncmp("", key))
//		all_was_good = load_tex(game, &game->map->tex.no_tex, get_value(splitted, "NO "));
//	else if (c == 'S')
//		all_was_good = load_tex(game, &game->map->tex.so_tex, get_value(splitted, "SO "));
//	else if (c == 'W')
//		all_was_good = load_tex(game, &game->map->tex.we_tex, get_value(splitted, "WE "));
//	else if (c == 'E')
//		all_was_good = load_tex(game, &game->map->tex.ea_tex, get_value(splitted, "EA "));
//	else if (c == 'S')
//		all_was_good = load_tex(game, &game->map->tex.sp_tex, get_value(splitted, "SP "));
	return (1);
}

int	get_color(t_game *game, char *line, char c)
{

	return (1);
}

int	get_map(t_game *game, char *line)
{

	return (1);
}

int	parse_map(t_game *game, char *map_name)
{
	int		fd;
	char	*line;
	int		continue_read;

	continue_read = 1;
	if ((fd = open(map_name, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) < 3)
		{
			free(line);
			continue;
		}
		if (line[0] == 'R')
			continue_read = get_resolution(game, line);
//		else if (line || (line[0] == 'S' && line[1] == 'O') || line[0] == 'W' || line[0] == 'E' || line[0] == 'S')
//			continue_read = get_texture(game, line, line[0]);
		else if (line[0] == 'C' || line[0] == 'F')
			continue_read = get_color(game, line, line[0]);
		else if (line[0] == '1')
			continue_read = get_map(game, line);
		else
			free(line);
		if (!continue_read)
			return (0);
	}
	if (!is_structure_full(game))
		return (0);
	else
	{
		printf("w: %d, h: %d\n", game->image->width, game->image->height);
		printf("floor: %d\n", game->map->floor_color);
		printf("sky: %d\n", game->map->sky_color);
		printf("w no: %d\n", game->map->tex.no_tex->width);
		printf("w so: %d\n", game->map->tex.so_tex->width);
		printf("w we: %d\n", game->map->tex.we_tex->width);
		printf("w ea: %d\n", game->map->tex.ea_tex->width);
		printf("w sp: %d\n", game->map->tex.sp_tex->width);
	}
	return (0);
	return (1);
}