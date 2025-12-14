CC = cc

CFLAGS = -Wall -Wextra -g

MLX_FLAGS = -lmlx -L./mlx/ -lm -lXext -lX11

SRC_MANDATORY = ./mandatory/mlx.c  ./mandatory/parsing/parsing1.c ./mandatory/main.c ./mandatory/parsing/helper.c \
  ./mandatory/parsing/checks.c ./mandatory/parsing/inits.c ./mandatory/parsing/parse_helper1.c ./mandatory/parsing/parse_helper2.c \
  ./mandatory/rendering/dda.c ./mandatory/rendering/mlx_hooks.c ./mandatory/rendering/rend.c

OBJS_MANDATORY = $(SRC_MANDATORY:.c=.o)

NAME = cub3d

$(NAME): $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(MLX_FLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS_MANDATORY)

fclean: clean
	rm -rf $(NAME)

re: fclean all
	make clean
	./cub3d test.cub
mandatory: all

.PHONY: all clean fclean re

