/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:18:50 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/15 18:16:10 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	join_line(int fd, char **string)
{
	int		r;
	char	*s;
	char	*buffer;

	if (!(buffer = ft_strnew(BUFFER_SIZE + 1)))
		return (ERROR_CODE_GNL);
	if ((r = read(fd, buffer, BUFFER_SIZE)) <= 0)
	{
		free(buffer);
		return (r);
	}
	buffer[r] = '\0';
	if (!(s = ft_strnew(ft_strlen(*string) + (r + 1))))
		return (ERROR_CODE_GNL);
	if (*string)
	{
		s = ft_strncat(s, *string, ft_strlen(*string));
		free(*string);
	}
	*string = ft_strncat(s, buffer, r);
	free(buffer);
	if (!contains_char(*string, '\n'))
		return (join_line(fd, string));
	return (SUCCESS_CODE_GNL);
}

static int	get_only_string(char **line, char **string, int *index, int *index2)
{
	char	*tmp;
	char	*s2;
	char	*s;

	while ((*string)[*index] && (*string)[*index] != '\n')
		(*index) += -(*index - (*index + 1));
	if (!(s = ft_strnew(*index + 1)))
		return (ERROR_CODE_GNL);
	*line = ft_strncat(s, *string, *index);
	*index2 = ft_strlen(*string) - *index;
	if (!(*index2))
		return (free_string_and_return(string, EOF_CODE_GNL));
	if ((s2 = ft_strnew(*index2)))
	{
		tmp = ft_strncat(s2, *string + *index + 1, *index2 - 1);
		free(*string);
		*string = tmp;
		return (SUCCESS_CODE_GNL);
	}
	return (free_string_and_return(string, ERROR_CODE_GNL));
}

static int	get_line_from_str(char **string, char **line)
{
	int	index;
	int	index2;
	int	r;

	index = 0;
	index2 = 0;
	r = 0;
	if ((r = get_only_string(line, string, &index, &index2)) != 1)
		return (free_string_and_return(string, 0));
	return (SUCCESS_CODE_GNL);
}

int			get_next_line(int fd, char **line)
{
	static char	*string = NULL;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ERROR_CODE_GNL);
	if (!contains_char(string, '\n'))
	{
		if (join_line(fd, &string) == ERROR_CODE_GNL)
			return (free_string_and_return(&string, ERROR_CODE_GNL));
		if (!string)
		{
			*line = ft_strnew(1);
			return (EOF_CODE_GNL);
		}
	}
	return (get_line_from_str(&string, line));
}
