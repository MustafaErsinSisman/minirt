NAME 		= minirt
CC		= cc
CFLAGS 		= -Wall -Wextra -Werror -lm
SRCS		= minirt.c  vector_basic.c vector_geo.c
RM		= rm -f

LIBFT		= Libft/libft.a
COLLECTOR	= collector/collector.a
DIR_LIBFT	= Libft
DIR_COLLECTOR	= collector

all: $(NAME)

$(NAME): $(SRCS)
	make -s  -C $(DIR_LIBFT)
	make -s  -C $(DIR_COLLECTOR)
	$(CC) $(CFLAGS) $(SRCS) $(COLLECTOR) $(LIBFT) -o $(NAME)

run: $(NAME)
	@./$(NAME)

clean:
	make -s -C $(DIR_LIBFT) clean
	make -s -C $(DIR_COLLECTOR) clean

fclean:
	$(RM) $(NAME)
	make -s -C $(DIR_LIBFT) fclean
	make -s -C $(DIR_COLLECTOR) fclean

re: fclean all

.PHONY: all clean fclean bonus re
