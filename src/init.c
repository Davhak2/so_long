/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <davihako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:35:08 by davihako          #+#    #+#             */
/*   Updated: 2025/03/27 01:47:41 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_and_validate_map(t_game *game, char *filename)
{
	if (!is_mapfile_valid(game, filename))
		ft_error("Map contains empty lines", game);
	get_map_dimensions(game, filename);
	allocate_map(game, filename);
	validate_map(game, filename);
	count_map_objects(game);
	if (game->players != 1 || game->exits != 1 || game->total_coins == 0)
		ft_error("Invalid player/exit count.", game);
	check_objects(game);
}

t_game	*initialize_game(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error("Memory allocation failed!", NULL);
	validate_arguments(argc, argv, game);
	load_and_validate_map(game, argv[1]);
	return (game);
}

void	initialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Failed to initialize MLX", game);
	game->win = mlx_new_window(game->mlx, SIZE * game->col, SIZE * game->row,
			"so_long");
	if (!game->win)
		ft_error("Failed to create window", game);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 1L << 2, close_window, game);
	mlx_hook(game->win, 4, 1L << 2, mouse_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop_hook(game->mlx, render_loop, game);
}

void	run_game_loop(t_game *game)
{
	initialize_mlx(game);
	get_xpm(game);
	ft_make_map(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
	free_mlx_images(game);
}
