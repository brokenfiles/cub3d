/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:50:42 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/13 02:44:56 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_puterror(char *s)
{
	while (*s)
		write(2, &*(s++), 1);
}

int	quit(int code, char *message)
{
	if (code == EXIT_FAILURE)
	{
		ft_puterror("Error: ");
		ft_puterror(message);
		ft_puterror("\n");
	}
	exit(code);
	return (code);
}
