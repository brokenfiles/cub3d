/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 04:19:00 by pbondoer          #+#    #+#             */
/*   Updated: 2019/12/03 16:34:35 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf.h"
#include "libft.h"
#include <stddef.h>

static void	free_textures(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < TEX_MAP_SIZE)
		del_image(mlx, mlx->tex[i++]);
}

int			load_textures(t_mlx *mlx)
{
	static char	*map[TEX_MAP_SIZE] = { "brick.xpm", "sky.xpm", "metal.xpm",
		"stone.xpm", "grass.xpm", NULL };
	t_image		*img;
	int			i;
	char		*t;

	i = 1;
	while (i < TEX_MAP_SIZE && map[i - 1])
	{
		t = ft_strjoin((HI_RES ? "textures_hi/" : "textures/"), map[i - 1]);
		if ((img = xpm_image(t, mlx)) == NULL)
		{
			ft_strdel(&t);
			free_textures(mlx);
			return (1);
		}
		ft_strdel(&t);
		mlx->tex[i] = img;
		i++;
	}
	mlx->max_tex = i - 1;
	mlx->tex[0] = NULL;
	mlx->floor = mlx->tex[2];
	mlx->ceiling = mlx->tex[4];
	return (0);
}
