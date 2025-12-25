CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lXext -lX11

SRC_BONUS = ./bonus/mlx/mlx_hooks.c ./bonus/mlx/mlx.c \
                ./bonus/parsing/checks.c ./bonus/parsing/checks2.c \
                ./bonus/parsing/checks3.c ./bonus/parsing/checks4.c \
                ./bonus/parsing/fetchers.c ./bonus/parsing/fetchers2.c \
                ./bonus/parsing/ft_malloc.c ./bonus/parsing/helper.c \
                ./bonus/parsing/inits.c ./bonus/parsing/parse_helper1.c \
                ./bonus/parsing/parse_helper2.c ./bonus/parsing/parsing1.c \
                ./bonus/rendering/dda.c ./bonus/rendering/player_movement.c \
                ./bonus/rendering/rend.c ./bonus/rendering/rend2.c \
                ./bonus/parsing/fetchers3.c ./bonus/rendering/rend3.c ./bonus/main.c 

SRC_MANDATORY = ./mandatory/mlx/mlx_hooks.c ./mandatory/mlx/mlx.c \
                ./mandatory/parsing/checks.c ./mandatory/parsing/checks2.c \
                ./mandatory/parsing/checks3.c ./mandatory/parsing/checks4.c \
                ./mandatory/parsing/fetchers.c ./mandatory/parsing/fetchers2.c \
                ./mandatory/parsing/ft_malloc.c ./mandatory/parsing/helper.c \
                ./mandatory/parsing/inits.c ./mandatory/parsing/parse_helper1.c \
                ./mandatory/parsing/parse_helper2.c ./mandatory/parsing/parsing1.c \
                ./mandatory/rendering/dda.c ./mandatory/rendering/player_movement.c \
                ./mandatory/rendering/rend.c ./mandatory/rendering/rend2.c \
                ./mandatory/parsing/fetchers3.c ./mandatory/rendering/rend3.c ./mandatory/main.c 



OBJS_BONUS = $(SRC_BONUS:.c=.o)

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

bonus: $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS_MANDATORY) $(OBJS_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

