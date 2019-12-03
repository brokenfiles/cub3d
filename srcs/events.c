/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/03 15:41:11 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_key(int key, void *param)
{
	t_game *game;

	game = (t_game *) param;
	//mlx_clear_window(data->mlx_ptr, data->mlx_win);
	//printf("dist : %f\n", sqrt(pow((game->player->location.x - 1), 2) + pow((game->player->location.y - 0), 2)));
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	else if (key == K_UP) //avancer
	{
		game->player->location.x +=
				game->player->speed * cos((game->player->location.yaw / 360.0) * (float) (2 * M_PI));
		game->player->location.y -=
				game->player->speed * sin((game->player->location.yaw / 360.0) * (float) (2 * M_PI));
		display_full_range(game);
	}
	else if (key == K_DOWN)
	{
		game->player->location.x -=
				game->player->speed * cos((game->player->location.yaw / 360.0) * (float) (2 * M_PI));
		game->player->location.y +=
				game->player->speed * sin((game->player->location.yaw / 360.0) * (float) (2 * M_PI));
		display_full_range(game);
	}
	else if (key == K_LEFT)
	{
		direction_change(game->player, game->player->rotation_speed);
		display_full_range(game);
	}
	else if (key == K_RIGHT)
	{
		direction_change(game->player, -game->player->rotation_speed);
		display_full_range(game);
	}

	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP)
	{
		display_tri(game->data, game->player,
					init_tri(init_vector(15 * game->player->location.x, 15 * game->player->location.y), 15, 0xB9BCC2));
		display_tri(game->data, game->player,
					init_tri(init_vector(15 * game->player->location.x, 15 * game->player->location.y), 15, 0x4749FF));
	}
	//printf("direction : %d\n", game->player->location.yaw);
	//printf("cos : %f\n", cos((game->player->location.yaw / 360.0) * (float)(2 * M_PI)));
	//printf("sin : %f\n\n", sin((game->player->location.yaw / 360.0) * (float)(2 * M_PI)));
	return (1);
}
