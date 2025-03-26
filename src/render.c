#include "so_long.h"

void free_mlx_images(t_game *game)
{
	if (!game || !game->mlx)
		return;

	for (int i = 0; i < 2; i++) {
		if (game->player_frames[i]) {
			mlx_destroy_image(game->mlx, game->player_frames[i]);
			game->player_frames[i] = NULL;
		}
	}
	if (game->pics.wall)
		mlx_destroy_image(game->mlx, game->pics.wall);
	if (game->pics.place)
		mlx_destroy_image(game->mlx, game->pics.place);
	if (game->pics.exit)
		mlx_destroy_image(game->mlx, game->pics.exit);
	if (game->pics.coin)
		mlx_destroy_image(game->mlx, game->pics.coin);
	if (game->pics.enemy)
		mlx_destroy_image(game->mlx, game->pics.enemy);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

void do_stat(t_game *game, void *image, int y, int x)
{
	if (!game || !game->mlx || !game->win || !image)
		ft_error("Rendering error: Null pointer detected", game);
	x *= SIZE;
	y *= SIZE;
	if (image != game->pics.place)
		mlx_put_image_to_window(game->mlx, game->win, game->pics.place, x, y);
	mlx_put_image_to_window(game->mlx, game->win, image, x, y);
}

int render_loop(t_game *game)
{
	if (!game)
		return 1;
	update_animation(game);
	ft_make_map(game);
	render_step_counter(game);
	return 0;
}

void ft_make_map(t_game *game)
{
	int y = -1;
	while (++y < game->row) {
		int x = -1;
		while (++x < game->col) {
			if (game->map[y][x] == WALL)
				do_stat(game, game->pics.wall, y, x);
			else if (game->map[y][x] == FLOOR)
				do_stat(game, game->pics.place, y, x);
			else if (game->map[y][x] == MAP_EXIT)
				do_stat(game, game->pics.exit, y, x);
			else if (game->map[y][x] == COINS)
				do_stat(game, game->pics.coin, y, x);
			else if (game->map[y][x] == ENEMY)
				do_stat(game, game->pics.enemy, y, x);
		}
	}
	y = -1;
	while (++y < game->row) {
		int x = -1;
		while (++x < game->col) {
			if (game->map[y][x] == PLAYER && game->player_frames[game->anim_frame]) {
				mlx_put_image_to_window(game->mlx, game->win,
					game->player_frames[game->anim_frame],
					x * SIZE, y * SIZE);
			}
		}
	}
}

void update_animation(t_game *game)
{
	if (!game)
		return;

    game->anim_counter++;
	if (game->anim_counter >= 100) {
		game->anim_counter = 0;
		if (game->player_frames[0] && game->player_frames[1]) {
			game->anim_frame = (game->anim_frame + 1) % 2;
		}
	}
}

void	render_step_counter(t_game *game)
{
	char	*num;

	num = ft_itoa(game->step);
	if (!num)
		return ;
	mlx_put_image_to_window(game->mlx, game->win,
			game->pics.wall, 1, 0);
	mlx_string_put(game->mlx, game->win, 10, 70, 0xFFFFFF, "MOVES:");
	mlx_string_put(game->mlx, game->win, 40, 70, 0xFFFFFF, num);
	free(num);
}

void get_xpm(t_game *game)
{
	int width;
	int height;

	width = SIZE;
	height = SIZE;
	game->pics.wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", &width, &height);
	if (!game->pics.wall)
		ft_error("Failed to load wall.xpm", game);
	game->pics.place = mlx_xpm_file_to_image(game->mlx, "img/place.xpm", &width, &height);
	if (!game->pics.place)
		ft_error("Failed to load place.xpm", game);
	game->player_frames[0] = mlx_xpm_file_to_image(game->mlx, "img/player.xpm", &width, &height);
	game->player_frames[1] = mlx_xpm_file_to_image(game->mlx, "img/player2.xpm", &width, &height);
	if (!game->player_frames[0] || !game->player_frames[1])
		ft_error("Failed to load player animation frames", game);
	game->pics.exit = mlx_xpm_file_to_image(game->mlx, "img/exit.xpm", &width, &height);
	if (!game->pics.exit)
		ft_error("Failed to load exit.xpm", game);
	game->pics.coin = mlx_xpm_file_to_image(game->mlx, "img/coin.xpm", &width, &height);
	if (!game->pics.coin)
		ft_error("Failed to load coin.xpm", game);
	game->pics.enemy = mlx_xpm_file_to_image(game->mlx, "img/enemy.xpm", &width, &height);
	if (!game->pics.enemy)
		ft_error("Failed to load enemy.xpm", game);
	game->anim_frame = 0;
	game->anim_counter = 0;
}
