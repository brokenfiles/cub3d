/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:21:29 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/13 02:44:56 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2)
		return (quit(EXIT_FAILURE, "Too few arguments.\nUsage: ./cub3d <valid map>"));
	if (!(game = malloc(sizeof(struct s_game))))
		return (quit(EXIT_FAILURE, "Cannot allocate global game."));
	if (!(game->map = malloc(sizeof(struct s_map))))
		return (quit(EXIT_FAILURE, "Cannot allocate map."));
	if (!(game->image = malloc(sizeof(struct s_image))))
		return (quit(EXIT_FAILURE, "Cannot allocate image."));
	if (!(game->p = malloc(sizeof(struct s_player))) || !(game->p->pos = malloc(sizeof(struct s_vector))))
		return (quit(EXIT_FAILURE, "Cannot allocate player."));
	if (!(game->ptr = mlx_init()))
		return (quit(EXIT_FAILURE, "Cannot init MLX."));
	if (!fill_map(av[1], game))
		return (quit(EXIT_FAILURE, "Invalid map."));
	if (!(game->win = mlx_new_window(game->ptr, game->image->width, game->image->height, "Cub3d")))
		return (quit(EXIT_FAILURE, "Cannot init MLX window."));
	init_player(game->p);
	game->image = new_image(game, game->image->width, game->image->height);
	display_map(game, &game->image);
	//display_full_range(game);
	mlx_hook(game->win, 2, 1L << 0, handle_key, (void *)game);
	mlx_loop(game->ptr);
	free(game->map);
	free(game->p->pos);
	free(game->p);
}
