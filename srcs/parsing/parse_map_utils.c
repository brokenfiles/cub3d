/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 15:19:43 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/07 15:30:35 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		get_int_len(unsigned int nb)
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

int	free_and_return(void *allocated, int ret)
{
	free(allocated);
	return (ret);
}

int	is_structure_full(t_game *game)
{
	if (!game->image->width || !game->map->sky_color ||
		!game->map->floor_color || !game->map->tex.ea_tex ||
		!game->map->tex.no_tex || !game->map->tex.so_tex ||
		!game->map->tex.we_tex || !game->image->height)
		return (0);
	return (1);
}

char	*to_next_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c && *(str + 1))
			return (str + 1);
		str++;
	}
	return (NULL);
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