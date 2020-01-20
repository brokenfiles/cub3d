/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:34:16 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/20 19:34:16 by llaurent         ###   ########.fr       */
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
