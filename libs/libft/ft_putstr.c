/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:57:05 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/17 14:06:19 by llaurent         ###   ########.fr       */
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
