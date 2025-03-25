CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
MLX_FLAGS   = -lmlx -lXext -lX11 -lm

NAME        = so_long
SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft

SRC         = so_long.c map_validation.c render.c movement.c utils.c
OBJ         = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
