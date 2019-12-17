/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 18:32:40 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_player(t_player *p, int sign)
{
	p->pos->x += sign * p->speed * p->dir->x;
	p->pos->y += -sign * p->speed * p->dir->y;
}

void		rotate(t_vector *vec, float teta)
{
	float x;
	float c;
	float s;

	x = vec->x;
	c = cos(teta);
	s = sin(teta);
	vec->x = vec->x * c - vec->y * s;
	vec->y = x * s + vec->y * c;
}

int			handle_key(int key, void *param)
{
	static int	last_key_code;
	t_game		*game;
	int			wall;
	int			x;
	t_ray		*ray;

	game = (t_game *)param;

	if (last_key_code == 259 && key == 12)
		exit(EXIT_SUCCESS);
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	else if (key == K_UP || key == 37)
		move_player(game->p, 1);
	else if (key == K_DOWN || key == 35)
		move_player(game->p, -1);
	else if (key == K_LEFT || key == 36)
		rotate(game->p->dir, game->p->rot_speed/180.0f * M_PI);
	else if (key == K_RIGHT || key == 43)
		rotate(game->p->dir, -game->p->rot_speed/180.0f * M_PI);
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP || key == 43 || key == 36 || key == 35 || key == 37)
	{
		ft_bzero(game->image->ptr, game->image->width * game->image->height * game->image->bpp);
		draw_minimap(game);
		render(game);
		mlx_put_image_to_window(game->ptr, game->win, game->image->image, 0, 0);
	}
	last_key_code = key;
	return (1);
}