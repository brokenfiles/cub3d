/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2019/11/28 17:52:48 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_key(int key, void *param)
{
	//static int x = 50;
	//static int y = 50;
	t_game *game;

	game = (t_game *)param;
	//mlx_clear_window(data->mlx_ptr, data->mlx_win);
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	else if (key == K_UP) //avancer
	{
		if (game->map->map[(int)game->player->location.y][(int)game->player->location.x - 1] && game->map->map[(int)game->player->location.y][(int)game->player->location.x - 1] == '0')
		{
			display_rectangle(game->data, init_rectangle(init_dimension(20, 20), init_vector(20 * game->player->location.y, 20 * game->player->location.x), 0xB9BCC2));
			game->player->location.x -= 0.1;
			update_map(game->data, game->map, game->player);
		}
		//y-=10;
		//display_rectangle(param, init_rectangle(init_dimension(1920, 1080), init_vector(x, y), 0xFF60C5));
	}
	else if (key == K_DOWN)
	{
		if (game->map->map[(int)game->player->location.y][(int)game->player->location.x + 1] && game->map->map[(int)game->player->location.y][(int)game->player->location.x + 1] == '0')
		{
			display_rectangle(game->data, init_rectangle(init_dimension(20, 20), init_vector(20 * game->player->location.y, 20 * game->player->location.x), 0xB9BCC2));
			game->player->location.x += 0.1;
			update_map(game->data, game->map, game->player);
		}
		//y+=10;
		//display_rectangle(param, init_rectangle(init_dimension(200, 200), init_vector(x, y), 0xFF60C5));
	}
	else if (key == K_LEFT)
	{
		if (game->map->map[(int)game->player->location.y - 1][(int)game->player->location.x] && game->map->map[(int)game->player->location.y - 1][(int)game->player->location.x] == '0')
		{
			display_rectangle(game->data, init_rectangle(init_dimension(20, 20), init_vector(20 * game->player->location.y, 20 * game->player->location.x), 0xB9BCC2));

			game->player->location.y -= 0.1;
			update_map(game->data, game->map, game->player);
		}
		//x-=10;
		//display_rectangle(param, init_rectangle(init_dimension(200, 200), init_vector(x, y), 0xFF60C5));
	}
	else if (key == K_RIGHT)
	{
		if (game->map->map[(int)game->player->location.y + 1][(int)game->player->location.x] && game->map->map[(int)game->player->location.y + 1][(int)game->player->location.x] == '0')
		{
			display_rectangle(game->data, init_rectangle(init_dimension(20, 20), init_vector(20 * game->player->location.y, 20 * game->player->location.x), 0xB9BCC2));

			game->player->location.y += 0.1;
			update_map(game->data, game->map, game->player);
		}
		//x+=10;
		//display_rectangle(param, init_rectangle(init_dimension(200, 200), init_vector(x, y), 0xFF60C5));
	}
	return (1);
}
