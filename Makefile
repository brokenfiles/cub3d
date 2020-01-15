# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llaurent <llaurent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/27 14:21:29 by llaurent          #+#    #+#              #
#    Updated: 2020/01/15 18:45:18 by jchotel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSC		=	srcs/parsing/parse_map.c\
				srcs/parsing/parse_tex.c\
				srcs/parsing/parse_free.c\
				srcs/parsing/parse_utils.c\
				srcs/parsing/valid_map.c\
				srcs/parsing/default_textures.c\
				srcs/raytracing/display.c\
				srcs/raytracing/display_form.c\
				srcs/raytracing/display_bonus.c\
				srcs/raytracing/display_sprite.c\
				srcs/raytracing/display_map.c\
				srcs/raytracing/raytracing.c\
				srcs/textures/texture.c\
				srcs/textures/images.c\
				srcs/events/events.c\
				srcs/events/move.c\
				srcs/events/interaction.c\
				srcs/utils/errors.c\
				srcs/utils/handler_struct.c\
				srcs/utils/save_img.c\
				srcs/utils/matrice.c\
				srcs/utils/other.c\
				srcs/cub3d.c\
				libs/libft/ft_putstr.c\
				libs/libft/ft_split.c\
				libs/libft/ft_strcmp.c\
				libs/libft/ft_atoi.c\
				libs/libft/ft_isdigit.c\
				libs/libft/ft_strjoin.c\
				libs/libft/ft_isascii.c\
				libs/libft/ft_strlen.c\
				libs/libft/ft_strcpy.c\
				libs/libft/ft_strdup.c\
				libs/libft/ft_strncmp.c\
				libs/libft/ft_strnstr.c\
				libs/libft/ft_strchr.c\
				libs/libft/ft_stronly.c\
				libs/libft/ft_calloc.c\
				libs/libft/ft_lstadd_front.c\
				libs/libft/ft_lstadd_back.c\
				libs/libft/ft_lstclear.c\
				libs/libft/ft_lstdelone.c\
				libs/libft/ft_lstiter.c\
				libs/libft/ft_lstlast.c\
				libs/libft/ft_itoa.c\
				libs/libft/ft_lstmap.c\
				libs/libft/ft_lstnew.c\
				libs/libft/ft_bzero.c\
				libs/libft/ft_lstrev.c\
				libs/libft/ft_lstsize.c\
				libs/get_next_line/get_next_line.c\
				libs/get_next_line/get_next_line_utils.c
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
			@${CC} ${OBJS} -L ./ -lmlx -framework AppKit -framework OpenGL -o ${NAME}
			@echo "\033[1;32m┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
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

rc:			re
			@make clean

%:
	@:

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

run: ${NAME}
	@make clean
	@echo "\033[1;34mRunning ${NAME}...\033[0;0m"
	@sh check_errors.sh $(call args,defaultstring)


.PHONY:		all clean fclean re
