/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:10:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/01/14 18:46:28 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		free_and_return(void *allocated, int ret)
{
	free(allocated);
	return (ret);
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

int		free_entire_parsing(t_game *game)
{
	free_entire_map(game->map->map);
	free(game->map->tex.no_tex);
	free(game->map->tex.so_tex);
	free(game->map->tex.we_tex);
	free(game->map->tex.ea_tex);
	free(game->map->tex.sp_tex);
	free(game->map->tex.li_tex);
	free(game->map->tex.do_tex);
	free(game->map->tex.co_tex);
	free(game->map->tex.lu_tex);
	return (1);
}
