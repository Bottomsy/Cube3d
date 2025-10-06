CC = cc

CFLAGS = -Wall -Wextra

MLX_FLAGS = -lmlx -L/usr/include/minilibx-linux/ -lXext -lX11

SRC = parsing/parsing1.c main.c

OBJS = $(SRC:.c=.o)

NAME = cub3d

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

