/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:58:42 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_nbr_length(unsigned int nb)
{
	unsigned int	index;

	index = 0;
	while (nb >= 10)
	{
		nb /= 10;
		index++;
	}
	return (index + 1);
}

char		*ft_itoa(int nbr)
{
	char			*str;
	unsigned int	nb;
	unsigned int	index;
	unsigned int	size;

	nb = (nbr < 0 ? (unsigned int)(-nbr) : (unsigned int)nbr);
	size = (unsigned int)get_nbr_length(nb);
	index = 0;
	if (!(str = (char*)malloc(sizeof(char) * (size + (nbr < 0 ? 2 : 1)))))
		return (0);
	if (nbr < 0)
	{
		str[index] = '-';
		size++;
	}
	index = size - 1;
	while (nb >= 10)
	{
		str[index--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[index] = (char)(nb % 10 + 48);
	str[size] = '\0';
	return (str);
}