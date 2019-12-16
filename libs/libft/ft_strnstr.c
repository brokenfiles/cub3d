/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:47:54 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 13:05:46 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	size;

	str = (char *)haystack;
	size = ft_strlen(needle);
	if (!needle || !haystack)
		return (NULL);
	if (size == 0)
		return (str);
	while (*str && len >= size)
	{
		if (ft_strncmp(str, (char *)needle, size) == 0)
			return (str);
		len--;
		++str;
	}
	return (NULL);
}
