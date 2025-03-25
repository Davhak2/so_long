#include "so_long.h"

void	ft_error(char *s, t_game *game)
{
	ft_putendl_fd(s, 2);
	if (game)
	{
		if (game->fd > 0)
			close(game->fd);
		if (game->map)
		{
			for (int i = 0; i < game->row; i++)
				free(game->map[i]);
			free(game->map);
		}
		free(game);
	}
	exit(EXIT_FAILURE);
}

void	get_map_dimensions(t_game *game, char *filename)
{
	int		fd;
	int		check;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file.", game);
	game->row = 0;
	game->col = 0;
	check = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->col = ft_strlen(line) - (line[ft_strlen(line) - 1] == '\n');
		if (!check)
			check = game->col;
		game->row++;
		free(line);
		if (game->col != check)
			ft_error("Map must be rectangular.", game);
	}
	close(fd);
	if (game->row <= 0 || game->col <= 0)
		ft_error("Invalid map dimensions.", game);
}

int	game_imgs(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (1);
	len = ft_strlen(str) - 1;
	i = -1;
	while (++i < len)
	{
		if (str[i] != WALL && str[i] != COINS && str[i] != ENEMY
			&& str[i] != PLAYER && str[i] != MAP_EXIT && str[i] != FLOOR)
			return (1);
	}
	return (0);
}

void	check_other_objects(t_game *game, char *filename)
{
	char	*tmp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Failed to open file.", game);
	for (int i = 0; i < game->row; i++)
	{
		tmp = get_next_line(fd);
		if (!tmp || game_imgs(tmp))
		{
			if (tmp)
				free(tmp);
			close(fd);
			ft_error("File validation error.", game);
		}
		free(tmp);
	}
	close(fd);
}

void	check_walls(t_game *game, char *filename)
{
	char	*tmp;
	int		fd;

	fd = open(filename, O_RDONLY);
	for (int i = 0; i < game->row; i++)
	{
		tmp = get_next_line(fd);
		if (i == 0 || i == game->row - 1)
		{
			for (int j = 0; j < game->col; j++)
			{
				if (tmp[j] != WALL)
				{
					free(tmp);
					close(fd);
					ft_error("File validation error.", game);
				}
			}
		}
		else
		{
			if (tmp[0] != WALL || tmp[game->col - 1] != WALL)
			{
				free(tmp);
				close(fd);
				ft_error("File validation error.", game);
			}
		}
		free(tmp);
	}
	close(fd);
}

void	allocate_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file.", game);
	game->map = (char **)malloc(sizeof(char *) * game->row);
	if (!game->map)
		ft_error("Memory allocation failed!", game);
	i = 0;
	while (i < game->row)
	{
		line = get_next_line(fd);
		if (!line)
			ft_error("Failed to read map line.", game);
		game->map[i] = ft_strtrim(line, "\n");
		free(line);
		if (!game->map[i])
			ft_error("Memory allocation failed!", game);
		i++;
	}
	close(fd);
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
