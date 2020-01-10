/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:01:32 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/10 12:47:26 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*final_string;
	unsigned int	index;
	unsigned int	index2;

	index2 = 0;
	index = ft_strlen(s1);
	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!(final_string = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	final_string = ft_strcpy(final_string, s1);
	while (index < (ft_strlen(s1) + ft_strlen(s2)))
	{
		final_string[index] = s2[index - ft_strlen(s1)];
		index++;
	}
	final_string[index] = '\0';
	return (final_string);
}
