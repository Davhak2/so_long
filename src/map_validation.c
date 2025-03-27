/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <davihako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:35:29 by davihako          #+#    #+#             */
/*   Updated: 2025/03/27 17:41:45 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	read_map_lines(t_game *g, int fd, int *dims)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (dims[0] == -1)
			dims[0] = len;
		else if (len != dims[0])
		{
			free(line);
			ft_error("Map must be rectangular", g);
		}
		dims[1]++;
		free(line);
		line = get_next_line(fd);
	}
}

void	get_map_dimensions(t_game *game, char *filename)
{
	int		fd;
	int		dims[2];

	dims[0] = -1;
	dims[1] = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file", game);
	read_map_lines(game, fd, dims);
	close(fd);
	if (dims[1] <= 0 || dims[0] <= 0)
		ft_error("Invalid map dimensions", game);
	game->row = dims[1];
	game->col = dims[0];
}

static void	validate_line(t_game *g, char *line, int row_idx)
{
	int	i;

	i = 0;
	while (i < g->col)
	{
		if (!valid_char(line[i]))
			ft_error("Invalid map character", g);
		if ((row_idx == 0 || row_idx == g->row - 1) && line[i] != WALL)
			ft_error("Map not surrounded by walls", g);
		if ((i == 0 || i == g->col - 1) && line[i] != WALL)
			ft_error("Map not surrounded by walls", g);
		i++;
	}
}

void	validate_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	char	*tmp;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file", game);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, "\n");
		validate_line(game, tmp, i);
		free(line);
		free(tmp);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	allocate_map(t_game *g, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file", g);
	g->map = (char **)malloc(sizeof(char *) * (g->row + 1));
	if (!g->map)
		ft_error("Memory allocation failed", g);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		g->map[i] = ft_strtrim(line, "\n");
		free(line);
		if (!g->map[i])
			ft_error("Memory allocation failed", g);
		line = get_next_line(fd);
		i++;
	}
	g->map[i] = NULL;
	close(fd);
}
