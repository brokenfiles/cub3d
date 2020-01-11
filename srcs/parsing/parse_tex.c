/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:10:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/10 21:49:29 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		load_nbrs(t_game *game)
{
	int index;
	char *path;
	char *extension;
	char *number;

	index = 0;
	while (index < 10)
	{
		number = ft_itoa(index);
		path = ft_strjoin("textures/numbers/", index != 0 ? number : "0");
		extension = ft_strjoin(path, ".XPM");
		if (!load_tex(game, &game->map->tex.nbrs[index], extension))
		{
			free(extension);
			free(path);
			free(number);
			return (quit(game, EXIT_FAILURE, "Texture error."));
		}
		free(extension);
		free(path);
		free(number);
		index++;
	}
	return (1);
}

int		get_texture(t_game *game, char *line, int *tex_counter)
{
	int	good;

	good = 1;
	if (!ft_strncmp(line, "NO ", 3))
		good = load_tex(game, &game->map->tex.no_tex, get_val(line, "NO "));
	else if (!ft_strncmp(line, "SO ", 3))
		good = load_tex(game, &game->map->tex.so_tex, get_val(line, "SO "));
	else if (!ft_strncmp(line, "WE ", 3))
		good = load_tex(game, &game->map->tex.we_tex, get_val(line, "WE "));
	else if (!ft_strncmp(line, "EA ", 3))
		good = load_tex(game, &game->map->tex.ea_tex, get_val(line, "EA "));
	else if (!ft_strncmp(line, "S ", 2))
		good = load_tex(game, &game->map->tex.sp_tex, get_val(line, "S "));
	else if (!ft_strncmp(line, "LU ", 3))
		good = load_tex(game, &game->map->tex.lu_tex, get_val(line, "LU "));
	else if (!ft_strncmp(line, "LI ", 3))
		good = load_tex(game, &game->map->tex.li_tex, get_val(line, "LI "));
	else if (!ft_strncmp(line, "CO ", 3))
		good = load_tex(game, &game->map->tex.co_tex, get_val(line, "CO "));
	else if (!ft_strncmp(line, "DO ", 3))
		good = load_tex(game, &game->map->tex.do_tex, get_val(line, "DO "));
	good ? (*tex_counter)++ : good;
	load_nbrs(game); //verifier avec louis
	return (good);
}

int		get_color(t_game *game, char *line, char c)
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
			break ;
	}
	if (index < 3)
		return (0);
	if (c == 'F')
		game->map->floor_color = convert_rgb(colors[0], colors[1], colors[2]);
	else if (c == 'C')
		game->map->sky_color = convert_rgb(colors[0], colors[1], colors[2]);
	return (1);
}
