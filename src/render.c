#include "so_long.h"

void	free_mlx_images(t_game *game)
{
	// int	i;

	// i = 0;
	mlx_destroy_image(game->mlx, game->pics.wall);
	mlx_destroy_image(game->mlx, game->pics.place);
	mlx_destroy_image(game->mlx, game->pics.exit);
	mlx_destroy_image(game->mlx, game->pics.player);
	mlx_destroy_image(game->mlx, game->pics.coin);
	mlx_destroy_image(game->mlx, game->pics.enemy);

	for (int i = 0; i < 2; i++)
	{
        if (game->player_frames[i])
            mlx_destroy_image(game->mlx, game->player_frames[i]);
    }
	mlx_destroy_window(game->mlx, game->win);
	// mlx_destroy_image(game->mlx, game->img.exit);
	// mlx_destroy_image(game->mlx, game->img.enemy);
	// while (i < 10)
	// {
	// 	mlx_destroy_image(game->mlx, game->img->coin[i]);
	// 	++i;
	// }
}


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

int render_loop(t_game *game)
{
    update_animation(game);
    ft_make_map(game);
    return (0);
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
            if (game->map[y][x] == PLAYER) {
                mlx_put_image_to_window(game->mlx, game->win,
                    game->player_frames[game->anim_frame],
                    x * SIZE, y * SIZE);
            }
        }
    }
}

void update_animation(t_game *game)
{
    game->anim_counter++;
    if (game->anim_counter >= 100)
	{
        game->anim_counter = 0;
        game->anim_frame = (game->anim_frame + 1) % 2;
    }
}

void render_step_counter(t_game *game)
{
    char    *steps_str;
    char    *step_message;
    int     color;
 //   int     bg_color;

    color = 0xFFFFFF;
  //  bg_color = 0x000000;
    step_message = "Steps: ";
    steps_str = ft_itoa(game->step);
    mlx_set_font(game->mlx, game->win, "9x15bold");
    mlx_string_put(game->mlx, game->win, 20, 20, color, step_message);
    mlx_string_put(game->mlx, game->win, 70, 20, color, steps_str);

    free(steps_str);
}

void	get_xpm(t_game *game)
{
	int	width;
	int	height;

	width = SIZE;
	height = SIZE;
	game->pics.wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", &width,
			&height);
	game->pics.place = mlx_xpm_file_to_image(game->mlx, "img/place.xpm", &width,
			&height);
    game->player_frames[0] = mlx_xpm_file_to_image(game->mlx, "img/player.xpm", &width, &height);
    game->player_frames[1] = mlx_xpm_file_to_image(game->mlx, "img/player2.xpm", &width, &height);
	game->pics.exit = mlx_xpm_file_to_image(game->mlx, "img/exit.xpm", &width,
			&height);
	game->pics.coin = mlx_xpm_file_to_image(game->mlx, "img/coin.xpm", &width,
			&height);
	game->pics.enemy = mlx_xpm_file_to_image(game->mlx, "img/enemy.xpm", &width,
			&height);

	game->anim_frame = 0;
    game->anim_counter = 0;

	for (int i = 0; i < 2; i++) {
        if (!game->player_frames[i])
            ft_error("Failed to load player animation frames", game);
    }
	if (!game->pics.wall || !game->pics.place || !game->pics.exit
		|| !game->pics.coin || !game->pics.enemy)
		ft_error("Failed to load images", game);
}
