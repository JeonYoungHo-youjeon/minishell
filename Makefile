NAME = minishell

SRCS		=	main.c \
			./builtins/ft_pwd.c \
			./builtins/ft_env.c \
			./builtins/ft_cd.c \
			./builtins/ft_echo.c \
			./builtins/ft_export.c \
			./builtins/ft_unset.c \
			./builtins/ft_exit.c \
			./builtins/ft_getenv.c \
			./builtins/env_utils.c \
			./executor/executor.c \
			./executor/fd_handling.c \
			./executor/heredoc.c \
			./executor/path.c \
			./executor/file.c \
			./utiles/ft_isalnum.c \
			./utiles/ft_itoa.c \
			./utiles/ft_split.c \
			./utiles/ft_strcmp.c \
			./utiles/ft_strjoin.c \
			./utiles/ft_strlen.c \
			./utiles/ft_strncmp.c \
			./utiles/ft_strlcpy.c \
			./utiles/ft_strdup.c


OBJS		= $(SRCS:%.c=%.o)

CC = gcc
CFLAGS = -Werror -Wall -Wextra
# READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
# READLINE_INC	= -I/opt/homebrew/opt/readline/include
READLINE_LIB 	= -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC	= -I${HOME}/.brew/opt/readline/include

FT_DIR	= ./libft
FT 	= ft

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		gcc $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean		:
		rm -f $(OBJS)

fclean		:	clean
		rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
