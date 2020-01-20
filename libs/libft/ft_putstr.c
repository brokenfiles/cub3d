/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:33:55 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:33:55 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	int	index;

	if (!str)
		return ;
	index = 0;
	while (str[index])
	{
		write(1, &str[index], 1);
		index++;
	}
}

void	ft_puterror(char *str)
{
	if (!str)
		return ;
	while (*str)
		write(2, &*(str++), 1);
}
