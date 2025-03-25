#include "so_long.h"

int	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	if (y < 0 || y >= game->col || x < 0 || x >= game->row)
		return (0);
	if (map_copy[x][y] == '1' || map_copy[x][y] == 'E')
		return (0);
	if (map_copy[x][y] == 'C')
		game->coins++;
	map_copy[x][y] = '1';
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x - 1, y);
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
	return (game->coins == game->total_coins);
}

int	check_exit(t_game *game, char **map_copy, int x, int y)
{
	if (x < 0 || x >= game->row || y < 0 || y >= game->col)
		return (0);
	if (map_copy[x][y] == 'E')
		return (1);
	if (map_copy[x][y] == '1' || map_copy[x][y] == 'X')
		return (0);
	map_copy[x][y] = 'X';
	if (check_exit(game, map_copy, x + 1, y) || check_exit(game, map_copy, x
			- 1, y) || check_exit(game, map_copy, x, y + 1) || check_exit(game,
			map_copy, x, y - 1))
		return (1);
	return (0);
}

char	**duplicate_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)ft_calloc(game->row + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	for (i = 0; i < game->row; i++)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			while (i-- > 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
	}
	map_copy[i] = NULL;
	return (map_copy);
}
void	free_map_copy(char **arr, int j)
{
	int	i;

	i = -1;
	while (++i < j)
		free(arr[i]);
	free(arr);
}

int	mouse_hook(int keycode, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	char	**map_copy;

	if (argc != 2)
		ft_error("Usage: ./so_long map.ber", NULL);
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error("Memory allocation failed!", NULL);
	game->filelen = ft_strlen(argv[1]);
	if (game->filelen <= 4 || ft_strncmp(&argv[1][game->filelen - 4], ".ber",
			4) != 0)
		ft_error("Map file must have .ber extension", game);
	if (!is_mapfile_valid(game, argv[1]))
		ft_error("Invalid map file", game);
	get_map_dimensions(game, argv[1]);
	allocate_map(game, argv[1]);
	check_other_objects(game, argv[1]);
	check_walls(game, argv[1]);
	game->total_coins = 0;
	for (int x = 0; x < game->row; x++)
	{
		for (int y = 0; y < game->col; y++)
		{
			if (game->map[x][y] == COINS)
				game->total_coins++;
			else if (game->map[x][y] == PLAYER)
			{
				game->players++;
				game->x_pos = x;
				game->y_pos = y;
			}
			else if (game->map[x][y] == MAP_EXIT)
				game->exits++;
		}
	}
	if (game->players != 1 || game->exits != 1 || game->total_coins == 0)
		ft_error("Invalid player/exit count.", game);
	map_copy = duplicate_map(game);
	if (!map_copy)
		ft_error("Failed to duplicate map for blocked exit check.", game);
	if (!check_exit(game, map_copy, game->x_pos, game->y_pos))
	{
		free_map_copy(map_copy, game->row);
		ft_error("Exit space blocked.", game);
	}
	free_map_copy(map_copy, game->row);
	map_copy = duplicate_map(game);
	if (!map_copy)
		ft_error("Failed to duplicate map for flood-fill check.", game);
	if (!flood_fill(game, map_copy, game->x_pos, game->y_pos))
	{
		free_map_copy(map_copy, game->row);
		ft_error("No valid path to collect all coins or reach exit.", game);
	}
	free_map_copy(map_copy, game->row);
	game->coins = 0;
	game->step = 0;
	game->frame = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Failed to initialize MLX", game);
	game->win = mlx_new_window(game->mlx, SIZE * game->col, SIZE * game->row,
			"so_long");
	if (!game->win)
		ft_error("Failed to create window", game);
	get_xpm(game);
	ft_make_map(game);
	mlx_hook(game->win, 17, 1L << 2, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
	free_mlx_images(game);
	exit(EXIT_SUCCESS);
}
