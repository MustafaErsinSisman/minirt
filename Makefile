NAME 	= minirt
CC		= cc
CFLAGS 	= -Wall -Wextra -Werror
SRCS	= minirt.c  vector.c
OBJS	= $(SRCS:.c=.o)
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

run: $(NAME)
	@./$(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
