/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:19:11 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:10:48 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		contains_char(char *s, char c)
{
	int	index;

	index = 0;
	if (!s)
		return (0);
	while (s[index])
	{
		if (s[index] == c)
			return (SUCCESS_CODE_GNL);
		index++;
	}
	return (0);
}

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	unsigned int	len;
	unsigned int	index;

	index = 0;
	len = ft_strlen(dest);
	while (src[index] && index < nb)
		dest[len++] = src[index++];
	dest[len] = 0;
	return (dest);
}

char	*ft_strnew(size_t n)
{
	char	*string;
	int		index;

	if (!(string = (char *)malloc(n + 1)))
		return (NULL);
	index = 0;
	string[index] = 0;
	while (index < n)
		string[index++] = 0;
	return (string);
}

int		free_string_and_return(char **string, int val)
{
	if (*string)
		free(*string);
	*string = NULL;
	return (val);
}
