CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./mandatory/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lXext -lX11

SRC_MANDATORY = ./mandatory/mlx.c \
                ./mandatory/parsing/parsing1.c \
                ./mandatory/main.c \
                ./mandatory/parsing/helper.c \
                ./mandatory/parsing/checks.c \
                ./mandatory/parsing/inits.c \
                ./mandatory/parsing/parse_helper1.c \
                ./mandatory/parsing/parse_helper2.c \
                ./mandatory/rendering/dda.c \
                ./mandatory/rendering/mlx_hooks.c \
                ./mandatory/rendering/rend.c \
                ./mandatory/rendering/test.c \
                ./mandatory/parsing/ft_malloc.c

OBJS_MANDATORY = $(SRC_MANDATORY:.c=.o)

NAME = cub3d

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS_MANDATORY)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

