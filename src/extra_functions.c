/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <davihako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:38:38 by davihako          #+#    #+#             */
/*   Updated: 2025/03/27 17:45:03 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *s, t_game *game)
{
	ft_putendl_fd(s, 2);
	if (game)
	{
		if (game->fd > 0)
			close(game->fd);
		if (game->map)
			ft_free_matrix(game->map);
		if (game->mlx)
			free_mlx_images(game);
		free(game);
	}
	exit(EXIT_FAILURE);
}

int	is_mapfile_valid(t_game *game, char *filename)
{
	char	*tmp;

	game->fd = open(filename, O_RDONLY);
	if (game->fd == -1)
		ft_error("Failed to open file.", game);
	tmp = get_next_line(game->fd);
	if (!tmp)
	{
		close(game->fd);
		ft_error("Empty or invalid file.", game);
	}
	while (tmp)
	{
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

int	valid_char(char c)
{
	return (c == WALL || c == COINS || c == ENEMY
		|| c == PLAYER || c == MAP_EXIT || c == FLOOR);
}

int	render_loop(t_game *game)
{
	if (!game)
		return (1);
	update_animation(game);
	render_step_counter(game);
	return (0);
}

void	step_done(t_game *game)
{
	game->step++;
	render_step_counter(game);
}
