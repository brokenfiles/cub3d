/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:50:42 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/06 10:53:43 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_puterror(char *s)
{
	while (*s)
		write(2, &*(s++), 1);
}

int free_map(char **map, int counter)
{
	if (!map || !*map)
		return (0);
	while (counter >= 0)
	{
		if (map[counter])
			free(map[counter]);
		counter--;
	}
	free(map);
	return (0);
}

int quit(t_game *game, int code, char *message)
{
	int index;

	index = 0;
	if (code == EXIT_FAILURE)
	{
		ft_puterror("Error: ");
		ft_puterror(message);
		ft_puterror("\n");
	}
	if (game && game->p)
		free(game->p);
	if (game && game->image)
		free(game->image);
	if (game && game->ptr)
		free(game->ptr);
	if (game && game->win)
		free(game->win);
//	if (game && game->map->tex.sp_tex)
//		free(game->map->tex.sp_tex);
//	if (game && game->map->tex.ea_tex)
//		free(game->map->tex.ea_tex);
//	if (game && game->map)
//		free(game->map->tex.we_tex);
//	if (game && game->map)
//		free(game->map->tex.so_tex);
//	if (game && game->map)
//		free(game->map->tex.no_tex);


//TODO: unmute that shit
//	while (game && game->map->map[index])
//		index++;
//	if (game)
//		free_map(game->map->map, index);
//	if (game)
//		free(game);
//	system("leaks cub3d");
	exit(code);
	return (code);
}
