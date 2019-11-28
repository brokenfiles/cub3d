/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:21:29 by llaurent          #+#    #+#             */
/*   Updated: 2019/11/28 18:00:46 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2)
		return (quit(EXIT_FAILURE, "Too few arguments.\nUsage: ./cub3d <valid map>"));
	if (!(game = malloc(sizeof(struct s_game))))
		return (quit(EXIT_FAILURE, "Cannot allocate global game."));
	if (!(game->data = malloc(sizeof(struct s_data))))
		return (quit(EXIT_FAILURE, "Cannot allocate game data."));
	if (!(game->map = malloc(sizeof(struct s_map))))
		return (quit(EXIT_FAILURE, "Cannot allocate map."));
	if (!(game->player = malloc(sizeof(struct s_player))))
		return (quit(EXIT_FAILURE, "Cannot allocate player."));
	if (!fill_map(av[1], game->map, game->data, game->player))
		return (quit(EXIT_FAILURE, "Invalid map."));
	if (!(game->data->mlx_ptr = mlx_init()))
		return (quit(EXIT_FAILURE, "Cannot init MLX."));
	if (!(game->data->mlx_win = mlx_new_window(game->data->mlx_ptr, game->data->width, game->data->height, "Cub3d")))
		return (quit(EXIT_FAILURE, "Cannot init MLX window."));
	//display_map(game->data, game->map, game->player);
	//display_rectangle(data, init_rectangle(init_dimension(100, 100), init_vector(100, 100), 0xFF60C5));
	display_triangle(game->data, init_triangle(init_vector(100, 500), init_vector(700, 5), 0x7EFF3B));
	mlx_hook(game->data->mlx_win, 2, 1L << 0, handle_key, (void *)game);
	mlx_loop(game->data->mlx_ptr);
	free(game->data);
	free(game->map);
	free(game->player);
}