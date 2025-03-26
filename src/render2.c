/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:35:58 by davihako          #+#    #+#             */
/*   Updated: 2025/03/26 22:36:00 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_mlx_images(t_game *game)
{
	int	i;

	if (!game || !game->mlx)
		return ;
	i = -1;
	while (++i < 2)
	{
		if (game->player_frames[i])
		{
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

int	render_loop(t_game *game)
{
	if (!game)
		return (1);
	update_animation(game);
	render_step_counter(game);
	return (0);
}
void	free_animations(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->row)
	{
		x = -1;
		while (++x < game->col)
		{
			if (game->map[y][x] == PLAYER
				&& game->player_frames[game->anim_frame])
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->player_frames[game->anim_frame], x * SIZE, y * SIZE);
			}
		}
	}
}

void	ft_make_map(t_game *game)
{
	int	x;
	int	y;

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
			else if (game->map[y][x] == COINS)
				do_stat(game, game->pics.coin, y, x);
			else if (game->map[y][x] == ENEMY)
				do_stat(game, game->pics.enemy, y, x);
		}
	}
	free_animations(game);
}
