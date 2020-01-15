/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:58:46 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 15:46:32 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		next_level(t_game *game)
{
	free_entire_parsing(game);
	if (!parse_map(game, game->level_names[game->level]))
		return (quit(game, EXIT_FAILURE, MSG_MAP_ERROR));
	return (1);
}

int			handle_key(int key, void *param)
{
	static int	last_key;
	static int	last_level;
	t_game		*game;
	int			wall;

	game = (t_game *)param;
	if ((last_key == K_Q && key == K_COMM) || key == K_ESC)
		quit(game, EXIT_SUCCESS, NULL);
	if (key == K_E)
		interact(game);
	move(game, key);
	if (last_level != game->level)
	{
		if (game->level < game->total_level)
		{
			next_level(game);
			last_level = game->level;
		}
		else
		{
//			printf("END\n");
		}
	}
	if (key == K_RIGHT || key == K_LEFT || key == K_DOWN || key == K_UP
	|| key == K_S || key == K_W || key == K_A || key == K_D || key == K_E
	|| key == K_MINUS || key == K_PLUS || key == K_DIGIT_0 || key == K_DIGIT_9
	|| key == K_DIGIT_7 || key == K_DIGIT_8)
		if (!render(game))
			return (quit(game, EXIT_FAILURE, MSG_RENDERING_ERROR));
	last_key = key;
	return (1);
}
