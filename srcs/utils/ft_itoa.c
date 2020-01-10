/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:58:42 by llaurent          #+#    #+#             */
/*   Updated: 2019/08/18 23:01:21 by elaachac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_nbrlen(int nbr, int len, unsigned int unbr)
{
	if (nbr < 0)
		unbr = -nbr;
	while (unbr)
	{
		unbr = unbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	unsigned int	unbr;
	int				len;
	char			*nbr_final;

	len = 0;
	unbr = nbr;
	len = ft_nbrlen(nbr, len, unbr);
	if (!(nbr_final = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (nbr < 0)
	{
		nbr_final[0] = '-';
		unbr = -nbr;
	}
	nbr_final[len] = '\0';
	len--;
	while (unbr >= 10)
	{
		nbr_final[len] = unbr % 10 + '0';
		unbr = unbr / 10;
		len--;
	}
	nbr_final[len] = unbr % 10 + '0';
	return (nbr_final);
}
