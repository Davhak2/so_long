/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luminous <luminous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:35:17 by davihako          #+#    #+#             */
/*   Updated: 2025/03/27 01:48:22 by luminous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_objects(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	game->total_coins = 0;
	game->players = 0;
	game->exits = 0;
	while (++x < game->row)
	{
		y = -1;
		while (++y < game->col)
		{
			if (game->map[x][y] == COINS)
				game->total_coins++;
			else if (game->map[x][y] == PLAYER)
			{
				game->players++;
				game->x_pos = x;
				game->y_pos = y;
			}
			else if (game->map[x][y] == MAP_EXIT)
				game->exits++;
		}
	}
}

void	check_objects(t_game *game)
{
	char	**map_copy;

	map_copy = duplicate_map(game);
	if (!map_copy)
		ft_error("Failed to duplicate map for blocked exit check.", game);
	if (!check_exit(game, map_copy, game->x_pos, game->y_pos))
	{
		free_map_copy(map_copy, game->row);
		ft_error("Exit space blocked.", game);
	}
	free_map_copy(map_copy, game->row);
	map_copy = duplicate_map(game);
	if (!map_copy)
		ft_error("Failed to duplicate map for flood-fill check.", game);
	if (!flood_fill(game, map_copy, game->x_pos, game->y_pos))
	{
		free_map_copy(map_copy, game->row);
		ft_error("No valid path to collect all coins or reach exit.", game);
	}
	free_map_copy(map_copy, game->row);
	game->coins = 0;
	game->step = 0;
}

void	validate_arguments(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		ft_error("Usage: ./so_long map.ber", NULL);
	game->filelen = ft_strlen(argv[1]);
	if (game->filelen <= 4 || ft_strncmp(&argv[1][game->filelen - 4], ".ber",
			4))
		ft_error("Map file must have .ber extension", game);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = initialize_game(argc, argv);
	run_game_loop(game);
	free_mlx_images(game);
	exit(EXIT_SUCCESS);
}
