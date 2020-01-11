/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:21:29 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/11 04:10:26 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		close_red_button(t_game *game)
{
	quit(game, EXIT_SUCCESS, NULL);
	return (0);
}

int		set_flags(int ac, char **av, t_game *game)
{
	int nb_flag;

	nb_flag = 0;
	game->disable_map = 0;
	game->disable_bonus = 0;
	game->save_first_image = 0;
	if (ft_strcmp(av[ac - 1], ARGUMENT_SAVE) == 0)
	{
		game->save_first_image = 1;
		nb_flag++;
		if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_MAP) == 0)
		{
			game->disable_map = 1;
			nb_flag++;
			if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_BONUS) == 0)
			{
				game->disable_bonus = 1;
				nb_flag++;
			}
		}
		else if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_BONUS) == 0)
		{
			game->disable_bonus = 1;
			nb_flag++;
			if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_MAP) == 0)
			{
				game->disable_map = 1;
				nb_flag++;
			}
		}
	}
	else if (ft_strcmp(av[ac - 1], ARGUMENT_DISABLE_MAP) == 0)
	{
		game->disable_map = 1;
		nb_flag++;
		if (ft_strcmp(av[ac - 2], ARGUMENT_SAVE) == 0)
		{
			game->save_first_image = 1;
			nb_flag++;
			if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_BONUS) == 0)
			{
				game->disable_bonus = 1;
				nb_flag++;
			}
		}
		else if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_BONUS) == 0)
		{
			game->disable_bonus = 1;
			nb_flag++;
			if (ft_strcmp(av[ac - 2], ARGUMENT_SAVE) == 0)
			{
				game->save_first_image = 1;
				nb_flag++;
			}
		}
	}
	else if (ft_strcmp(av[ac - 1], ARGUMENT_DISABLE_BONUS) == 0)
	{
		game->disable_bonus = 1;
		nb_flag++;
		if (ft_strcmp(av[ac - 2], ARGUMENT_SAVE) == 0)
		{
			game->save_first_image = 1;
			nb_flag++;
			if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_MAP) == 0)
			{
				game->disable_map = 1;
				nb_flag++;
			}
		}
		else if (ft_strcmp(av[ac - 2], ARGUMENT_DISABLE_MAP) == 0)
		{
			game->disable_map = 1;
			nb_flag++;
			if (ft_strcmp(av[ac - 2], ARGUMENT_SAVE) == 0)
			{
				game->save_first_image = 1;
				nb_flag++;
			}
		}
	}
	return (nb_flag);
}

int		main(int ac, char **av, char **env)
{
	t_game	*game;
	int		nb_flag;
	int		nb_levels;

	if (ac < 2)
		return (quit(game, EXIT_FAILURE, MSG_TOO_FEW_ARGUMENTS));
	if (!(game = init_game()))
		return (quit(NULL, EXIT_FAILURE, MSG_CANNOT_ALLOCATE_GAME_ERROR));
	nb_flag = set_flags(ac, av, game);
	nb_levels = ac - 1 - nb_flag;
	init_level(game, nb_levels, av);
	if (!(game->ptr = mlx_init()))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_INIT_MLX_ERROR));
	if (!parse_map(game, av[game->level + 1]))
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	if (!(game->win = mlx_new_window(game->ptr, game->image->width, game->image->height, GAME_NAME)))
		return (quit(game, EXIT_FAILURE, MSG_CANNOT_INIT_MLX_WINDOW_ERROR));
	if (!(game->image = new_image(game, game->image->width, game->image->height)))
		return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	mlx_hook(game->win, 2, 1L << 0, handle_key, (void *)game);
	mlx_hook(game->win, 17, 1L << 0, close_red_button, (void *)game);
	if (!render(game))
		return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
//	system("leaks cub3d");
	mlx_loop(game->ptr);
}
