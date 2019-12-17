/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:47:38 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/17 11:16:38 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	int	index;

	index = 0;
	while (s1[index] && (s1[index] == s2[index]) &&
	(unsigned int)index < n - 1)
		index++;
	if (n == 0)
		return (0);
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
