/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stronly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:39:26 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:16:10 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_stronly(const char *s, const char *s2)
{
	int index;

	index = 0;
	while (s2[index])
	{
		if (!ft_strchr(s, s2[index]))
			return (0);
		index++;
	}
	return (1);
}
