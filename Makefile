NAME = so_long
NAME_BONUS = so_long_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L ./mlx_linux/ -lmlx -Ilmlx -lXext -lX11

RM = rm -rf

SRCS = src/ libft/libft.a
#SRCS_BONUS = src_bonus/pipex_bonus.c src_bonus/utils_bonus.c libft/libft.a src_bonus/norm_bonus.c

$(NAME): libft/libft.a $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

$(NAME_BONUS): libft/libft.a $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME_BONUS)

libft/libft.a:
	make -C libft

all: $(NAME)

bonus: $(NAME_BONUS)

clean:
	$(RM) $(NAME) $(NAME_BONUS)
	make clean -C libft

fclean: clean
	make fclean -C libft

re: fclean all

.PHONY:	all clean fclean re
