/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:17:52 by llaurent          #+#    #+#             */
/*   Updated: 2020/01/06 16:59:51 by llaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define SUCCESS_CODE_GNL 1
# define EOF_CODE_GNL 0
# define ERROR_CODE_GNL -1
# define BUFFER_SIZE 32

int				get_next_line(int fd, char **line);
int				contains_char(char *s, char c);
int				free_string_and_return(char **str, int return_value);
#endif
