/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/16 19:20:25 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		next_level(t_game *game)
{
	free_entire_parsing(game);
	if (!parse_map(game, game->level_names[game->level]))
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	return (game->level);
}

int		is_key(int key, int last_key)
{
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP
		|| key == K_S || key == K_W || key == K_A || key == K_D || key == K_E
		|| key == K_MINUS || key == K_PLUS || key == K_DIGIT_0 || key == 49
		|| key == K_DIGIT_9 || key == K_DIGIT_7 || key == K_DIGIT_8)
		return (1);
	if ((last_key == K_Q && key == K_COMM) || key == K_ESC)
		return (2);
	if (key == 36)
		return (3);
	return (0);
}

int		handle_key(int key, void *param)
{
	static int	last_key;
	static int	last_level;
	static int	next;
	t_game		*game;

	game = (t_game *)param;
	if (is_key(key, last_key) == 2)
		quit(game, EXIT_SUCCESS, NULL);
	if (is_key(key, last_key) == 3 && game->step == STEP_START)
		game->step = STEP_PLAYING;
	if (game->step != STEP_PLAYING)
		return (1);
	interact(game, key);
	move(game, key);
	if (last_level != game->level)
	{
		if (game->level < game->total_level)
			last_level = next_level(game);
		else
			game->step = STEP_END;
	}
	if (is_key(key, last_key) == 1 || is_key(key, last_key) == 3)
		if (!render(game))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	last_key = key;
	return (1);
}
