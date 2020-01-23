/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:31:31 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/21 19:56:05 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		free_map(char **map, int counter)
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

int		quit(int code, char *message)
{
	int index;

	index = 0;
	if (code == EXIT_FAILURE)
	{
		ft_puterror("Error\n");
		ft_puterror(message);
		ft_puterror("\n");
	}
	exit(code);
	return (code);
}

int		fnq(void (*f)(void *), void *mem, int code, char *message)
{
	f(mem);
	return (quit(code, message));
}

int		close_red_button(void)
{
	return (quit(EXIT_SUCCESS, NULL));
}
