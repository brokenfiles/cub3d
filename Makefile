# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 14:21:29 by llaurent          #+#    #+#              #
#    Updated: 2019/12/03 16:34:34 by llaurent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSC		=	srcs/parse_map.c\
				srcs/handler_struct.c\
				libs/libft/ft_putstr.c\
				libs/libft/ft_split.c\
				libs/libft/ft_strcmp.c\
				libs/libft/ft_atoi.c\
				libs/libft/ft_isdigit.c\
				libs/libft/ft_strjoin.c\
				libs/libft/ft_strlen.c\
				libs/libft/ft_strcpy.c\
				libs/libft/ft_strdup.c\
				libs/libft/ft_strncmp.c\
				libs/libft/ft_strnstr.c\
				libs/libft/ft_strchr.c\
				libs/libft/ft_stronly.c\
				srcs/events.c\
				srcs/direction.c\
				srcs/display.c\
				srcs/errors.c\
				srcs/texture.c\
				srcs/images.c\
				srcs/cub3d.c
SRCSH		= includes/cub3d.h
OBJS		= $(SRCSC:%.c=%.o)
NAME		= cub3d
CC			= gcc
AR			= ar rc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

.c.o: ${OBJS}
	@${CC} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} ${SRCSH}
			@${CC} ${OBJS} -l mlx -framework AppKit -framework OpenGL -o ${NAME}
			@echo "\033[1;32m"
			@echo "┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"
			@echo "${NAME} generated successfully.\033[0;0m"

all:		${NAME}

clean:
			@echo "\033[1;35mDeleting .o files..\033[0;0m"
			@${RM} ${OBJS}

fclean:		clean
			@echo "\033[1;35mDeleting binary files..\033[0;0m"
			@${RM} ${NAME}

re:			fclean all

%:
	@:

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

run: ${NAME}
	@make clean
	@echo "\033[1;34mRunning ${NAME}...\033[0;0m"
	@sh check_errors.sh $(call args,defaultstring)


.PHONY:		all clean fclean re