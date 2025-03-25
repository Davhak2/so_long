#include "so_long.h"

int	key_hook(int keycode, t_game *game)
{
	int	prow;
	int	pcol;

	prow = check_player_row(game->map, game->row);
	pcol = check_player_col(game->map, game->row);
	if (keycode == KEY_W)
		return (hook_up(game, prow, pcol));
	if (keycode == KEY_S)
		return (hook_down(game, prow, pcol));
	if (keycode == KEY_A)
		return (hook_left(game, prow, pcol));
	if (keycode == KEY_D)
		return (hook_right(game, prow, pcol));
	if (keycode == KEY_ESC)
		free_var(game);

	render_step_counter(game);
	return (0);
}

int	hook_up(t_game *game, int prow, int pcol)
{
	if (game->map[prow - 1][pcol] != WALL && game->map[prow - 1][pcol] != MAP_EXIT)
		step_done(game);
	if (game->map[prow - 1][pcol] == MAP_EXIT
		&& game->coins == game->total_coins)
		free_var(game);
	if (game->map[prow - 1][pcol] != WALL && game->map[prow
		- 1][pcol] != MAP_EXIT)
	{
		if (game->map[prow - 1][pcol] == COINS)
			game->coins++;
		if (game->map[prow - 1][pcol] == ENEMY)
			free_var(game);
		game->map[prow - 1][pcol] = PLAYER;
		game->map[prow][pcol] = FLOOR;
		ft_make_map(game);
		render_step_counter(game);
		return (0);
	}
	else
		return (1);
}

int	hook_down(t_game *game, int prow, int pcol)
{
	if (game->map[prow + 1][pcol] != WALL && game->map[prow + 1][pcol] != MAP_EXIT)
		step_done(game);
	if (game->map[prow + 1][pcol] == MAP_EXIT
		&& game->coins == game->total_coins)
		free_var(game);
	if (game->map[prow + 1][pcol] != WALL && game->map[prow
		+ 1][pcol] != MAP_EXIT)
	{
		if (game->map[prow + 1][pcol] == COINS)
			game->coins++;
		if (game->map[prow + 1][pcol] == ENEMY)
			free_var(game);
		game->map[prow + 1][pcol] = PLAYER;
		game->map[prow][pcol] = FLOOR;
		ft_make_map(game);
		render_step_counter(game);
		return (0);
	}
	else
		return (1);
}

int	hook_left(t_game *game, int prow, int pcol)
{
	if (game->map[prow][pcol - 1] != WALL && game->map[prow][pcol-1] != MAP_EXIT)
		step_done(game);
	if (game->map[prow][pcol - 1] == MAP_EXIT
		&& game->coins == game->total_coins)
		free_var(game);
	if (game->map[prow][pcol - 1] != WALL && game->map[prow][pcol
		- 1] != MAP_EXIT)
	{
		if (game->map[prow][pcol - 1] == COINS)
			game->coins++;
		if (game->map[prow][pcol - 1] == ENEMY)
			free_var(game);
		game->map[prow][pcol - 1] = PLAYER;
		game->map[prow][pcol] = FLOOR;
		ft_make_map(game);
		render_step_counter(game);
		return (0);
	}
	else
		return (1);
}

int	hook_right(t_game *game, int prow, int pcol)
{
	if (game->map[prow][pcol + 1] != WALL && game->map[prow][pcol + 1] != MAP_EXIT)
		step_done(game);
	if (game->map[prow][pcol + 1] == MAP_EXIT
		&& game->coins == game->total_coins)
		free_var(game);
	if (game->map[prow][pcol + 1] != WALL && game->map[prow][pcol
		+ 1] != MAP_EXIT)
	{
		if (game->map[prow][pcol + 1] == COINS)
			game->coins++;
		if (game->map[prow][pcol + 1] == ENEMY)
			free_var(game);
		game->map[prow][pcol + 1] = PLAYER;
		game->map[prow][pcol] = FLOOR;
		ft_make_map(game);
		render_step_counter(game);
		return (0);
	}
	else
		return (1);
}
