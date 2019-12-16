/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:14:04 by llaurent          #+#    #+#             */
/*   Updated: 2019/12/16 13:05:46 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		index;
	char	*returned_string;

	index = 0;
	if (!(returned_string = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[index])
	{
		returned_string[index] = s1[index];
		index++;
	}
	returned_string[index] = '\0';
	return (returned_string);
}
