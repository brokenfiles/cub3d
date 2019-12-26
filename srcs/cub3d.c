/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:21:29 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 13:05:45 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		close_red_button(t_game *game)
{
	quit(game, EXIT_SUCCESS, NULL);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	t_game	*game;

	if (ac < 2)
		return (quit(game, EXIT_FAILURE, MSG_TOO_FEW_ARGUMENTS));
	if (!(game = init_game()))
		return (quit(NULL, EXIT_FAILURE, MSG_CANNOT_ALLOCATE_GAME_ERROR));
	game->disable_map = 0;
	game->save_first_image = 0;
	if (ac == 3)
	{
		if (ft_strcmp(av[2], ARGUMENT_SAVE) == 0)
			game->save_first_image = 1;
		if (ft_strcmp(av[2], ARGUMENT_DISABLE_MAP) == 0)
			game->disable_map = 1;
	}
	if (ac == 4)
		if (ft_strcmp(av[3], ARGUMENT_DISABLE_MAP) == 0)
			game->disable_map = 1;
	if (!(game->p = malloc(sizeof(struct s_player))))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_ALLOCATE_PLAYER_ERROR));
	if (!(game->ptr = mlx_init()))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_INIT_MLX_ERROR));
	if (!fill_map(av[1], game))
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	if (!(game->win = mlx_new_window(game->ptr, game->image->width, game->image->height, GAME_NAME)))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_INIT_MLX_WINDOW_ERROR));
	init_player(game->p);
	if (!(game->image = new_image(game, game->image->width, game->image->height)))
		return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	mlx_hook(game->win, 2, 1L << 0, handle_key, (void *)game);
	mlx_hook(game->win, 17, 1L << 0, close_red_button, (void *)game);
	if (!render(game))
		return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	mlx_loop(game->ptr);
	free(game->map);
	free(game->p);
}
