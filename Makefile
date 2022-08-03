# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunkyle <hyunkyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 10:50:54 by hyunkyle          #+#    #+#              #
#    Updated: 2022/08/02 21:09:34 by hyunkyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS				= pipex.c \
					  pipex_child_utils.c \
					  pipex_utils1.c \
					  pipex_utils2.c \
					 
					  
OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = cc

NAME = pipex

$(NAME)	: $(OBJS)
	make -C ./get_next_line
	make -C ./libft
	$(CC) $(FLAGS) -g -o $(NAME) $(OBJS) ./libft/libft.a ./get_next_line/libgnl.a -I pipex.h

all	: $(NAME)

bonus : all

clean	:
		make -C ./get_next_line clean
		make -C ./libft clean
		rm -f $(OBJS)

fclean	:	clean
		make -C ./get_next_line fclean
		make -C ./libft fclean
		rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
