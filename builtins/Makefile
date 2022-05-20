# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/17 15:50:40 by mher              #+#    #+#              #
#    Updated: 2022/05/20 18:26:05 by mher             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
	
NAME	= test

RM	= rm -f
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror

FT_DIR	= ./libft
FT 	= ft

SRCS	= \
	  test.c \
	  ft_pwd.c \
	  ft_env.c \
	  ft_cd.c \
	  update_envp.c \

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
