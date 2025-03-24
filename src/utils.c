#include "so_long.h"

int	check_player_row(char **map, int rows)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == PLAYER)
				return (y);
			x++;
		}
		y++;
	}
	return (-1);
}

int	check_player_col(char **map, int rows)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == PLAYER)
				return (x);
			x++;
		}
		y++;
	}
	return (-1);
}

void	step_done(t_game *game)
{
	game->step++;
	printf("Steps: %d\n", game->step);
}

void	free_var(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
	{
		for (int i = 0; i < game->row; i++)
			free(game->map[i]);
		free(game->map);
	}
	free(game);
	exit(0);
}

