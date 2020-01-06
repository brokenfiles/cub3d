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

int	is_structure_full(t_game *game)
{
	if (!game->image->width || !game->map->tex.sky_color ||
	!game->map->tex.floor_color || !game->map->tex.ea_tex ||
	!game->map->tex.no_tex || !game->map->tex.so_tex ||
	!game->map->tex.we_tex || !game->image->height)
		return (0);
	return (1);
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

	if (!(tmp = get_val(line, "R ")))
		return (0);
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
			fill_data(game, line);
		else
			printf("la map\n");
//		free(*line);
	}
	if (!is_structure_full(game))
		return (0);
	return (1);
}