#include "so_long.h"

void	ft_error(char *s, t_game *game)
{
	ft_putendl_fd(s, 2);
	if (game)
		free(game);
	exit(EXIT_FAILURE);
}

int	is_map_valid(t_game *game, char *filename)
{
	char	*tmp;

	game->fd = open(filename, O_RDONLY);
	if (game->fd == -1)
		ft_error("Failed to open file.", game);
	tmp = get_next_line(game->fd);
	while (tmp)
	{
		ft_putstr_fd(tmp, 1);
		if (tmp[0] == '\n')
		{
			free(tmp);
			close(game->fd);
			return (0);
		}
		free(tmp);
		tmp = get_next_line(game->fd);
	}
	close(game->fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		ft_error("Wrong arguments. It should be ./so_long NAME.ber", NULL);
	if (ft_strlen(argv[1]) < 4 || !ft_strnstr(&argv[1][ft_strlen(argv[1]) - 4], ".ber", 4))
		ft_error("Files name must end with .ber", NULL);
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		ft_error("Memory allocation failed!", NULL);
	if (!is_map_valid(game, argv[1]))
	{
		ft_putendl_fd("KO", 2);
		free(game);
		exit(1);
	}
	ft_putendl_fd("OK", 1);
	free(game);
	return (0);
}
