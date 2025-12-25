CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lXext -lX11

SRC_BONUS = ./bonus/mlx/mlx_hooks_bonus.c ./bonus/mlx/mlx_bonus.c \
                ./bonus/parsing/checks_bonus.c ./bonus/parsing/checks2_bonus.c \
                ./bonus/parsing/checks3_bonus.c ./bonus/parsing/checks4_bonus.c \
                ./bonus/parsing/fetchers_bonus.c ./bonus/parsing/fetchers2_bonus.c \
                ./bonus/parsing/ft_malloc_bonus.c ./bonus/parsing/helper_bonus.c \
                ./bonus/parsing/inits_bonus.c ./bonus/parsing/parse_helper1_bonus.c \
                ./bonus/parsing/parse_helper2_bonus.c ./bonus/parsing/parsing1_bonus.c \
                ./bonus/rendering/dda_bonus.c ./bonus/rendering/player_movement_bonus.c \
                ./bonus/rendering/rend_bonus.c ./bonus/rendering/rend2_bonus.c \
                ./bonus/parsing/fetchers3_bonus.c ./bonus/rendering/rend3_bonus.c ./bonus/main_bonus.c 


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

NAME_B = cub3d_bonus

all: $(NAME)

bonus: $(NAME_B)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS_MANDATORY)
	$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBFT) $(MLX_FLAGS) -o $(NAME)


$(NAME_B): $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_B)


clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -rf $(OBJS_MANDATORY) $(OBJS_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re

