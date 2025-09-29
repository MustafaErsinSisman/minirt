NAME		= minirt
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
LDLIBS		= vector/vector.a collector/collector.a Libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -lm

SRCS		= minirt.c
OBJS		= $(SRCS:.c=.o)

RM		= rm -f

DIR_LIBFT	= Libft
DIR_COLLECTOR	= collector
DIR_VECTOR	= vector
DIR_MINILBIX	= minilibx-linux

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C $(DIR_LIBFT)
	make -s -C $(DIR_COLLECTOR)
	make -s -C $(DIR_VECTOR)
	make -s -C $(DIR_MINILBIX)
	$(CC) $(OBJS) $(LDLIBS) -o $(NAME)

run: all
	@./$(NAME)

leak:all
	valgrind --leak-check=full --show-leak-kinds=all ./${NAME}

clean:
	$(RM) $(OBJS)
	make -s -C $(DIR_LIBFT) clean
	make -s -C $(DIR_COLLECTOR) clean
	make -s -C $(DIR_VECTOR) clean
	make -s -C $(DIR_MINILBIX) clean

fclean: clean
	$(RM) $(NAME)
	make -s -C $(DIR_LIBFT) fclean
	make -s -C $(DIR_COLLECTOR) fclean
	make -s -C $(DIR_VECTOR) fclean
	make -s -C $(DIR_MINILBIX) clean

re: fclean all

.PHONY: all clean fclean re
