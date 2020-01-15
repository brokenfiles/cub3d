/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:21:29 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		close_red_button(t_game *game)
{
	quit(game, EXIT_SUCCESS, NULL);
	return (0);
}

int		get_flags(int ac, char **av, t_game *game)
{
	while (*av)
	{
		if (ft_strlen(*av) > 4 &&
		ft_strcmp(*av + ft_strlen(*av) - 4, ".cub") == 0 &&
		game->total_level < MAX_LEVEL)
			game->level_names[game->total_level++] = *av;
		else
		{
			if (ft_strcmp(*av, ARGUMENT_SAVE) == 0)
				game->save_first_image = 1;
			else if (ft_strcmp(*av, ARGUMENT_DISABLE_MAP) == 0)
				game->disable_map = 1;
			else if (ft_strcmp(*av, ARGUMENT_DISABLE_BONUS) == 0)
				game->disable_bonus = 1;
			else
				return (0);
		}
		av++;
	}
	if (game->total_level == 0)
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2)
		return (quit(game, EXIT_FAILURE, MSG_TOO_FEW_ARGUMENTS));
	if (!(game = init_game()))
		return (quit(NULL, EXIT_FAILURE, MSG_CANNOT_ALLOCATE_GAME_ERROR));
	if (!(get_flags(ac - 1, av + 1, game)))
		return (quit(game, EXIT_FAILURE, MSG_ARGUMENTS_ERROR));
	if (!(game->ptr = mlx_init()))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_INIT_MLX_ERROR));
	if (!parse_map(game, game->level_names[0]))
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	if (!(game->win = mlx_new_window(game->ptr, game->dim.x, game->dim.y, GAME_NAME)))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_INIT_MLX_WINDOW_ERROR));
//	system("leaks cub3d");
	if (!(game->image = new_image(game, game->dim.x, game->dim.y)))
		return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
//	system("leaks cub3d");
	mlx_hook(game->win, 2, 1L << 0, handle_key, (void *)game);
	mlx_hook(game->win, 17, 1L << 0, close_red_button, (void *)game);
	if (!render(game))
		return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
//	system("leaks cub3d");
	mlx_loop(game->ptr);
	return (0);
}
