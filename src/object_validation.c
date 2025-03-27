/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:35:46 by davihako          #+#    #+#             */
/*   Updated: 2025/03/26 22:35:48 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	if (y < 0 || y >= game->col || x < 0 || x >= game->row)
		return (0);
	if (map_copy[x][y] == '1' || map_copy[x][y] == 'E')
		return (0);
	if (map_copy[x][y] == 'C')
		game->coins++;
	map_copy[x][y] = '1';
	flood_fill(game, map_copy, x + 1, y);
	flood_fill(game, map_copy, x - 1, y);
	flood_fill(game, map_copy, x, y + 1);
	flood_fill(game, map_copy, x, y - 1);
	return (game->coins == game->total_coins);
}

int	check_exit(t_game *game, char **map_copy, int x, int y)
{
	if (x < 0 || x >= game->row || y < 0 || y >= game->col)
		return (0);
	if (map_copy[x][y] == 'E')
		return (1);
	if (map_copy[x][y] == '1' || map_copy[x][y] == 'X')
		return (0);
	map_copy[x][y] = 'X';
	if (check_exit(game, map_copy, x + 1, y) || check_exit(game, map_copy, x
			- 1, y) || check_exit(game, map_copy, x, y + 1) || check_exit(game,
			map_copy, x, y - 1))
		return (1);
	return (0);
}

char	**duplicate_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)ft_calloc(game->row + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = -1;
	while (++i < game->row)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			while (i-- > 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	free_map_copy(char **arr, int j)
{
	int	i;

	i = -1;
	while (++i < j)
		free(arr[i]);
	free(arr);
}
