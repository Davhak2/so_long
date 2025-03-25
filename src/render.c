#include "so_long.h"

void	do_stat(t_game *game, void *image, int y, int x)
{
	if (!game || !game->mlx || !game->win || !image)
		ft_error("Rendering error: Null pointer detected", game);
	x *= SIZE;
	y *= SIZE;
	if (image != game->pics.place)
		mlx_put_image_to_window(game->mlx, game->win, game->pics.place, x, y);
	mlx_put_image_to_window(game->mlx, game->win, image, x, y);
}

void	ft_make_map(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->row)
	{
		x = -1;
		while (++x < game->col)
		{
			if (game->map[y][x] == WALL)
				do_stat(game, game->pics.wall, y, x);
			else if (game->map[y][x] == FLOOR)
				do_stat(game, game->pics.place, y, x);
			else if (game->map[y][x] == MAP_EXIT)
				do_stat(game, game->pics.exit, y, x);
			else if (game->map[y][x] == PLAYER)
				do_stat(game, game->pics.player, y, x);
			else if (game->map[y][x] == COINS)
				do_stat(game, game->pics.coin, y, x);
			else if (game->map[y][x] == ENEMY)
				do_stat(game, game->pics.enemy, y, x);
		}
	}
}

void	get_xpm(t_game *game)
{
	int	width;
	int	height;

	width = SIZE;
	height = SIZE;
	game->pics.wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", &width, &height);
	game->pics.place = mlx_xpm_file_to_image(game->mlx, "img/place.xpm", &width, &height);
	game->pics.player = mlx_xpm_file_to_image(game->mlx, "img/player.xpm", &width, &height);
	game->pics.exit = mlx_xpm_file_to_image(game->mlx, "img/exit.xpm", &width, &height);
	game->pics.coin = mlx_xpm_file_to_image(game->mlx, "img/coin.xpm", &width, &height);
	game->pics.enemy = mlx_xpm_file_to_image(game->mlx, "img/enemy.xpm", &width, &height);
	if (!game->pics.wall || !game->pics.place || !game->pics.player ||
		!game->pics.exit || !game->pics.coin || !game->pics.enemy)
		ft_error("Failed to load images", game);
}
