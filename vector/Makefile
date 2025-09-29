SRCS = vector_basic.c vector_geo.c

OBJS = $(SRCS:.c=.o)
BONUSOBJS = $(BONUS:.c=.o)

NAME = vector.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
