/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 21:42:09 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:12:50 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int index;

	index = 0;
	while (s[index])
	{
		if (s[index] == c)
			return ((char *)&s[index]);
		index++;
	}
	if (s[index] == c)
		return ((char *)&s[index]);
	return (0);
}
