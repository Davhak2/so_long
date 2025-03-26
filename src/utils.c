/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:36:37 by davihako          #+#    #+#             */
/*   Updated: 2025/03/26 22:36:39 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	render_step_counter(game);
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

int	mouse_hook(int keycode, t_game *game)
{
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
}
