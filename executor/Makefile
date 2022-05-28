# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 15:50:40 by mher              #+#    #+#              #
#    Updated: 2022/05/28 15:15:51 by mher             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
	
NAME	= test

RM	= rm -f
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

FT_DIR	= ./libft
FT 	= ft

SRCS	= \
	  ./builtins/ft_pwd.c \
	  ./builtins/ft_env.c \
	  ./builtins/ft_cd.c \
	  ./builtins/ft_echo.c \
	  ./builtins/ft_export.c \
	  ./builtins/ft_unset.c \
	  ./builtins/ft_exit.c \
	  ./builtins/env_utils.c \
	  executor.c \
	  redirection.c \
	  test.c \

OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(MAKE) -C $(FT_DIR) 
	$(CC) $(CFLAGS) -o  $@ $^ \
		-L$(FT_DIR) -l$(FT) \

all : $(NAME)

clean :
	$(MAKE) clean -C $(FT_DIR)
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) fclean -C $(FT_DIR)
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all bonus clean fclean re
