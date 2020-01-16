/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:50:42 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/16 11:09:08 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		ft_puterror("Error\n");
		ft_puterror(message);
		ft_puterror("\n");
	}
//	system("leaks cub3d");
	exit(code);
	return (code);
}
