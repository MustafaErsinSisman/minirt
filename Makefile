NAME 			= minirt
CC				= cc
CFLAGS 			= -Wall -Wextra -Werror
SRCS			= minirt.c  vector.c
RM				= rm -f

LIBFT			= Libft/libft.a
COLLECTOR		= collector/collector.a
DIR_LIBFT		= libft
DIR_COLLECTOR	= collector

all: $(NAME)

$(NAME): $(SRCS)
	make -s  -C $(DIR_LIBFT)
	make -s  -C $(DIR_COLLECTOR)
	$(CC) $(CFLAGS) $(SRCS) $(COLLECTOR) $(LIBFT) $(LIBFLAGS) -o $(NAME)

run: $(NAME)
	@./$(NAME)

clean:
	make -s -C $(DIR_LIBFT) clean
	make -s -C $(DIR_COLLECTOR) clean

fclean: clean
	@$(RM) $(NAME)
	make -s -C $(DIR_LIBFT) fclean
	make -s -C $(DIR_COLLECTOR) fclean

re: fclean all

.PHONY: all clean fclean bonus re
