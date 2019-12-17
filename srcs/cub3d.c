/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:21:29 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 17:55:24 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		close_red_button(t_game *game)
{
	(void)game;
	quit(EXIT_SUCCESS, NULL);
	return (0);
}

int		main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2)
		return (quit(EXIT_FAILURE, "Too few arguments.\nUsage: ./cub3d <valid map>"));
	if (!(game = malloc(sizeof(struct s_game))))
		return (quit(EXIT_FAILURE, "Cannot allocate global game."));
	if (ac == 3)
		if (ft_strcmp(av[2], "-save") == 0)
			game->save_first_image = 1;
	if (!(game->map = malloc(sizeof(struct s_map))))
		return (quit(EXIT_FAILURE, "Cannot allocate map."));
	if (!(game->image = malloc(sizeof(struct s_image))))
		return (quit(EXIT_FAILURE, "Cannot allocate image."));
	if (!(game->p = malloc(sizeof(struct s_player))) || !(game->p->pos = malloc(sizeof(struct s_vector)))  || !(game->p->dir = malloc(sizeof(struct s_vector))))
		return (quit(EXIT_FAILURE, "Cannot allocate player."));
	if (!(game->ptr = mlx_init()))
		return (quit(EXIT_FAILURE, "Cannot init MLX."));
	if (!fill_map(av[1], game))
		return (quit(EXIT_FAILURE, "Invalid map."));
	if (!(game->win = mlx_new_window(game->ptr, game->image->width, game->image->height, "Cub3d")))
		return (quit(EXIT_FAILURE, "Cannot init MLX window."));
	init_player(game->p);
	game->image = new_image(game, game->image->width, game->image->height);
	mlx_hook(game->win, 2, 1L << 0, handle_key, (void *)game);
	mlx_hook(game->win, 17, 1L << 0, close_red_button, (void *)game);
	mlx_loop(game->ptr);
	free(game->map);
	free(game->p->pos);
	free(game->p);
}
