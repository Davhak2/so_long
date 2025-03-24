# Compiler and flags
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
MLX_FLAGS   = -lmlx -lXext -lX11 -lm

# Project name
NAME        = so_long

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft
INC_DIR     = includes

# Source files
SRC         = so_long.c map_validation.c graphics.c movement.c utils.c
OBJ         = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# libft library
LIBFT       = $(LIBFT_DIR)/libft.a

# Colors
GREEN       = \033[0;32m
RED         = \033[0;31m
NC          = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)🧹 Object files removed$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(RED)🧹 $(NAME) and libraries removed$(NC)"

re: fclean all

.PHONY: all clean fclean re
