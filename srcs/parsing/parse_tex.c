/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:10:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/17 13:22:46 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		fnl(t_game *game, t_image **tex, char *val)
{
	free(*tex);
	return (load_tex(game, tex, val));
}

int		v_tex(t_game *game, t_image **image, char *val, int *tc)
{
	int	good;
	int	already_set;

	already_set = *image != NULL;
	if (!already_set)
		good = load_tex(game, image, val);
	if (good && !already_set)
		(*tc)++;
	return (good);
}

int		load_nbrs(t_game *game)
{
	int		index;
	char	*path;
	char	*tmp;

	index = 0;
	if (!(game->map->tex.nbrs =
			(t_image **)malloc(sizeof(struct s_image *) * 10)))
		return (0);
	while (index < 10)
	{
		path = ft_itoa(index);
		tmp = path;
		path = ft_strjoin("textures/numbers/", index != 0 ? path : "0");
		free(tmp);
		tmp = path;
		path = ft_strjoin(path, ".XPM");
		free(tmp);
		if (!load_tex(game, &game->map->tex.nbrs[index], path))
			return (fnq(free, path, EXIT_FAILURE, "Texture error."));
		free(path);
		index++;
	}
	return (1);
}

int		get_texture(t_game *game, char *line, int *tc)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (v_tex(game, &game->map->tex.no_tex, get_val(line, "NO "), tc));
	else if (!ft_strncmp(line, "SO ", 3))
		return (v_tex(game, &game->map->tex.so_tex, get_val(line, "SO "), tc));
	else if (!ft_strncmp(line, "WE ", 3))
		return (v_tex(game, &game->map->tex.we_tex, get_val(line, "WE "), tc));
	else if (!ft_strncmp(line, "EA ", 3))
		return (v_tex(game, &game->map->tex.ea_tex, get_val(line, "EA "), tc));
	else if (!ft_strncmp(line, "S ", 2))
		return (v_tex(game, &game->map->tex.sp_tex, get_val(line, "S "), tc));
	else if (!ft_strncmp(line, "LU ", 3))
		return (fnl(game, &game->map->tex.lu_tex, get_val(line, "LU ")));
	else if (!ft_strncmp(line, "LI ", 3))
		return (fnl(game, &game->map->tex.li_tex, get_val(line, "LI ")));
	else if (!ft_strncmp(line, "CO ", 3))
		return (fnl(game, &game->map->tex.co_tex, get_val(line, "CO ")));
	else if (!ft_strncmp(line, "DO ", 3))
		return (fnl(game, &game->map->tex.do_tex, get_val(line, "DO ")));
	return (1);
}

int		get_color(t_game *game, char *line, char c)
{
	int		colors[3];
	int		index;
	char	*tmp;

	index = 0;
	tmp = line + 2;
	if (!tmp)
		return (0);
	while (index < 3)
	{
		colors[index++] = ft_atoi(tmp);
		if (!(tmp = to_next_char(tmp, ',')))
			break ;
	}
	if (index < 3)
		return (0);
	if (c == 'F')
		game->map->floor_color = convert_rgb(colors[0], colors[1], colors[2],
				1);
	else if (c == 'C')
		game->map->sky_color = convert_rgb(colors[0], colors[1], colors[2], 1);
	return (1);
}
