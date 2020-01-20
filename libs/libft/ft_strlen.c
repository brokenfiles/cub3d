/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:34:11 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:34:11 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlen(const char *str)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
		index++;
	return (index);
}

size_t	ft_strlen_wc(const char *str, char c)
{
	int	counter;

	counter = 0;
	while (*str)
		if (*(str++) != c)
			counter++;
	return (counter);
}
