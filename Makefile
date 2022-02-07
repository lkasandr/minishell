NAME =		minishell
SRCS =		./srcs/cd.c ./srcs/command_handler.c ./srcs/lexer.c  ./srcs/echo.c ./srcs/env.c ./srcs/error.c \
			./srcs/exec.c ./srcs/export_two.c ./srcs/export_utils.c ./srcs/export.c ./srcs/init.c ./srcs/lexer_five.c \
			./srcs/lexer_four.c ./srcs/lexer_three.c ./srcs/lexer_two.c ./srcs/main.c ./srcs/pipe_two.c ./srcs/pipe_utils.c \
			./srcs/pipe.c ./srcs/pwd.c ./srcs/redirect_four.c ./srcs/redirect_one.c ./srcs/redirect_three.c ./srcs/redirect_two.c \
			./srcs/signal.c ./srcs/unset.c ./srcs/util.c ./srcs/exit.c ./srcs/exec_two.c ./srcs/export_three.c
LIBFT =		libft
LIBS = 		./libft/libft.a 
OBJS =		$(SRCS:.c=.o)
HEADER = 	./srcs/minishell.h
%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) 


CC =		gcc
CFLAGS =	-Wall -Wextra  -Werror
FLAG =		-lreadline -ltermcap -g -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/
RM =		rm -f
all :		$(NAME) 

$(NAME) :	$(OBJS) $(LIBFT)
			$(MAKE) -C $(LIBFT) all
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER) $(LIBS) $(FLAG)
			@echo "minishell is ready"

$(LIBFT) :  libft/*.c libft/*.h
			$(MAKE) -C $(LIBFT) all
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER)


clean :		
			$(MAKE) -C $(LIBFT) clean
			$(RM) $(OBJS)

fclean 	:	clean
			$(MAKE) -C $(LIBFT) fclean
			$(RM) $(NAME)

re :		fclean all

norm:
			norminette srcs/*.c srcs/minishell.h libft/*.c libft/libft.h

.PHONY :	all clean fclean re norm
