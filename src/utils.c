/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <davihako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:36:41 by davihako          #+#    #+#             */
/*   Updated: 2025/03/28 19:27:24 by davihako         ###   ########.fr       */
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

void	free_var(t_game *game)
{
	free_mlx_images(game);
	if (game->map)
		ft_free_matrix(game->map);
	free(game);
	exit(0);
}

int	mouse_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_mlx_images(game);
		exit(0);
	}
	return (0);
}

int	close_window(t_game *game)
{
	free_var(game);
	exit(0);
}
