NAME = minishell

SRCS		=	main.c \
				
OBJS		= $(SRCS:%.c=%.o)

LIBC		= ar rc

CC = gcc
CFLAGS = -Werror -Wall -Wextra 
READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include


all			:	$(NAME)

$(NAME)		:	$(OBJS)
		gcc $(FLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean		:
		rm -f $(OBJS)
		
fclean		:	clean
		rm -f $(NAME)
		
re			:	fclean all

.PHONY		:	all clean fclean re bonus
