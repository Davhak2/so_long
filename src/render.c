/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:36:06 by davihako          #+#    #+#             */
/*   Updated: 2025/03/26 22:36:08 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_animation(t_game *game)
{
	if (!game)
		return ;
	game->anim_counter++;
	if (game->anim_counter >= 4000)
	{
		ft_make_map(game);
		game->anim_counter = 0;
		if (game->player_frames[0] && game->player_frames[1])
			game->anim_frame = (game->anim_frame + 1) % 2;
	}
}

static void	put_zoomed_text(t_game *game, int x, int y, char *text)
{
	int	dx;
	int	dy;

	dx = 0;
	while (dx < 2)
	{
		dy = 0;
		while (dy < 2)
		{
			mlx_string_put(game->mlx, game->win, x + dx, y + dy, 0xFFFFFF,
				text);
			dy++;
		}
		dx++;
	}
}

void	render_step_counter(t_game *game)
{
	char	*num;

	num = ft_itoa(game->step);
	if (!num)
		return ;
	put_zoomed_text(game, 10, 30, "STEPS:");
	put_zoomed_text(game, 55, 30, num);
	free(num);
}

void	get_xpm2(t_game *game)
{
	int	width;
	int	height;

	width = SIZE;
	height = SIZE;
	game->pics.exit = mlx_xpm_file_to_image(game->mlx, "img/exit.xpm", &width,
			&height);
	if (!game->pics.exit)
		ft_error("Failed to load exit.xpm", game);
	game->pics.coin = mlx_xpm_file_to_image(game->mlx, "img/coin.xpm", &width,
			&height);
	if (!game->pics.coin)
		ft_error("Failed to load coin.xpm", game);
	game->pics.enemy = mlx_xpm_file_to_image(game->mlx, "img/enemy.xpm", &width,
			&height);
	if (!game->pics.enemy)
		ft_error("Failed to load enemy.xpm", game);
	game->anim_frame = 0;
	game->anim_counter = 0;
}

void	get_xpm(t_game *game)
{
	int	width;
	int	height;

	width = SIZE;
	height = SIZE;
	game->pics.wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", &width,
			&height);
	if (!game->pics.wall)
		ft_error("Failed to load wall.xpm", game);
	game->pics.place = mlx_xpm_file_to_image(game->mlx, "img/place.xpm", &width,
			&height);
	if (!game->pics.place)
		ft_error("Failed to load place.xpm", game);
	game->player_frames[0] = mlx_xpm_file_to_image(game->mlx, "img/player.xpm",
			&width, &height);
	game->player_frames[1] = mlx_xpm_file_to_image(game->mlx, "img/player2.xpm",
			&width, &height);
	if (!game->player_frames[0] || !game->player_frames[1])
		ft_error("Failed to load player animation frames", game);
	get_xpm2(game);
}
