NAME	= collector.a
CC	= cc
CFLAGS	= -Wall -Werror -Wextra
SRCS	= collector.c utils.c 
OBJS	= $(SRCS:.c=.o)
RM	= rm -f
AR	= ar rc

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re