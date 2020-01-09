/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:10:57 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/09 14:17:06 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int	get_texture(t_game *game, char *line)
{
	int	all_was_good;

	all_was_good = 1;
	if (!ft_strncmp(line, "NO ", 3))
		all_was_good = load_tex(game, &game->map->tex.no_tex, get_val(line, "NO "));
	else if (!ft_strncmp(line, "SO ", 3))
		all_was_good = load_tex(game, &game->map->tex.so_tex, get_val(line, "SO "));
	else if (!ft_strncmp(line, "WE ", 3))
		all_was_good = load_tex(game, &game->map->tex.we_tex, get_val(line, "WE "));
	else if (!ft_strncmp(line, "EA ", 3))
		all_was_good = load_tex(game, &game->map->tex.ea_tex, get_val(line, "EA "));
	else if (!ft_strncmp(line, "S ", 2))
		all_was_good = load_tex(game, &game->map->tex.sp_tex, get_val(line, "S "));
	return (all_was_good);
}

int	get_color(t_game *game, char *line, char c)
{
	int		colors[3];
	int		index;
	char	*tmp;

	index = 0;
	tmp = line;
	while (index++ < 3)
	{
		colors[index - 1] = ft_atoi(tmp);
		if (!(tmp = to_next_char(tmp, ',')))
			break;
	}
	if (index < 3)
		return (0);
	if (c == 'F')
		game->map->floor_color = convert_rgb(colors[0], colors[1], colors[2]);
	else if (c == 'C')
		game->map->sky_color = convert_rgb(colors[0], colors[1], colors[2]);
	return (1);
}

int		free_entire_map(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_bzero(str[i], ft_strlen(str[i]));
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (1);
}

int		fill_temp_map(t_game *game, char *line, char **temp)
{
	(*temp) = ft_strnew(ft_strlen(game->map->map[0]) + ft_strlen(line) + 1);
	(*temp) = ft_strncat((*temp), game->map->map[0], ft_strlen(game->map->map[0]));
	(*temp) = ft_strncat((*temp), "\n", 1);
	(*temp) = ft_strncat((*temp), line, ft_strlen(line));
	free_entire_map(game->map->map);
	if (!(game->map->map = (char **)malloc(sizeof(char *) * 2)))
		return (0);
	game->map->map[0] = ft_strdup((*temp));
	game->map->map[1] = NULL;
	free((*temp));
	return (1);
}

int	get_map(t_game *game, char *line)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (game->map->map == NULL)
	{
		if (!(game->map->map = malloc(sizeof(char *) * 2)))
			return (0);
		game->map->map[0] = ft_strdup(line);
		game->map->map[1] = NULL;
		return (1);
	}
	fill_temp_map(game, line, &temp);
	return (1);
}

int	read_map(t_game *game, int fd)
{
	char	*line;
	int		continue_read;

	continue_read = 1;
	game->map->map = NULL;
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp(line, "R ", 2))
			continue_read = get_resolution(game, line);
		else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
				 || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
				 || !ft_strncmp(line, "S ", 2))
			continue_read = get_texture(game, line);
		else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
			continue_read = get_color(game, line, line[0]);
		else if (ft_strlen(line) > 0 && line[0] == '1')
			continue_read = get_map(game, line);
		free(line);
		if (!continue_read)
			return (0);
	}
	free(line);
	return (1);
}

int	parse_map(t_game *game, char *map_name)
{
	int		fd;
	char	*tmp;

	if ((fd = open(map_name, O_RDONLY)) == -1)
		return (0);
	if (!read_map(game, fd))
		return (0);
	if (!game->map->map)
		return (0);
	if (!(tmp = ft_strnew(ft_strlen(game->map->map[0]))))
	{
		free_entire_map(game->map->map);
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	}
	ft_strcpy(tmp, game->map->map[0]);
	free_entire_map(game->map->map);
	if (!(game->map->map = ft_split(tmp, "\n")))
	{
		free(tmp);
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	}
	free(tmp);
	if (!valid_map(game))
		return (0);
	if (!is_structure_full(game))
		return (0);
	return (1);
}