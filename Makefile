NAME = minishell

SRCS		=	main.c \
			./builtins/ft_pwd.c \
			./builtins/ft_env.c \
			./builtins/ft_cd.c \
			./builtins/ft_echo.c \
			./builtins/ft_export.c \
			./builtins/ft_unset.c \
			./builtins/ft_exit.c \
			./builtins/env_utils.c \
			./executor/executor.c \
			./executor/fd_handling.c \
			./executor/heredoc.c \
			./executor/path.c \
			./executor/file.c \

OBJS		= $(SRCS:%.c=%.o)

CC = gcc
CFLAGS = -Werror -Wall -Wextra 
READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

FT_DIR	= ./libft
FT 	= ft

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		$(MAKE) -C $(FT_DIR) \
		$(CC) $(FLAGS) -o $(NAME) $(OBJS) \
		$(READLINE_LIB) \
		-l$(FT) -L$(FT_DIR) \

%.o: %.c
	$(CC)  $(FLAGS) $(READLINE_INC) -c $< -o $@

clean		:
		$(MAKE) clean -C $(FT_DIR)
		rm -f $(OBJS)
		
fclean		:	clean
		$(MAKE) fclean -C $(FT_DIR)
		rm -f $(NAME)
		
re			:	fclean all

.PHONY		:	all clean fclean re bonus
