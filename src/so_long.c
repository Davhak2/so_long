#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		ft_error("Usage: ./so_long map.ber", NULL);
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error("Memory allocation failed!", NULL);
	game->filelen = ft_strlen(argv[1]);
	if (game->filelen <= 4 || ft_strncmp(&argv[1][game->filelen - 4], ".ber", 4) != 0)
		ft_error("Map file must have .ber extension", game);
	if (!is_mapfile_valid(game, argv[1]))
		ft_error("Invalid map file", game);
	get_map_dimensions(game, argv[1]);
	allocate_map(game, argv[1]);
	check_other_objects(game, argv[1]);
	check_walls(game, argv[1]);
	game->total_coins = 0;
	for (int y = 0; y < game->row; y++)
		for (int x = 0; x < game->col; x++)
			if (game->map[y][x] == COINS)
				game->total_coins++;
	game->coins = 0;
	game->step = 0;
	game->frame = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Failed to initialize MLX", game);
	game->win = mlx_new_window(game->mlx, SIZE * game->col, SIZE * game->row, "so_long");
	if (!game->win)
		ft_error("Failed to create window", game);
	get_xpm(game);
	ft_make_map(game);
	mlx_hook(game->win, 2, 1L<<0, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
