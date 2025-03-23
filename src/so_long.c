#include "so_long.h"

void	ft_error(char *s, t_game *game)
{
	ft_putendl_fd(s, 2);
	if (game)
	{
		if (game->fd > 0)
			close(game->fd);
		free(game);
	}
	exit(EXIT_FAILURE);
}

void	get_map_dimensions(t_game *game, char *filename)
{
	int		fd;
	int 	check;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_error("Failed to open file.", game);
	game->row = 0;
	game->col = 0;
	check = 0;
	while (!0)
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
			ft_error("File damaged.", game);
	}
	close(fd);
	if (game->row <= 0 || game->col <= 0)
		ft_error("Invalid map dimensions.", game);
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
void	get_xpm(t_game *game)
{
	game->width = IMG_HEIGHT;
	game->height = IMG_WIDTH;
	game->pics.wall = mlx_xpm_file_to_image(game->mlx, "img/wall.xpm",
			&game->height, &game->width);
	game->pics.place = mlx_xpm_file_to_image(game->mlx, "img/place.xpm",
			&game->height, &game->width);
	game->pics.player = mlx_xpm_file_to_image(game->mlx, "img/player.xpm",
			&game->height, &game->width);
	game->pics.player1 = mlx_xpm_file_to_image(game->mlx, "img/player1.xpm",
			&game->height, &game->width);
	game->pics.player2 = mlx_xpm_file_to_image(game->mlx, "img/player2.xpm",
			&game->height, &game->width);
	game->pics.player3 = mlx_xpm_file_to_image(game->mlx, "img/player3.xpm",
			&game->height, &game->width);
	game->pics.exit = mlx_xpm_file_to_image(game->mlx, "img/exit.xpm",
			&game->height, &game->width);
	game->pics.coll = mlx_xpm_file_to_image(game->mlx, "img/coll.xpm",
			&game->height, &game->width);
	game->pics.enemy = mlx_xpm_file_to_image(game->mlx, "img/enemy.xpm",
			&game->height, &game->width);
	game->pics.exit1 = mlx_xpm_file_to_image(game->mlx, "img/exit1.xpm",
			&game->height, &game->width);
}
int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		ft_error("Wrong arguments. It should be ./so_long NAME.ber", NULL);
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		ft_error("Memory allocation failed!", NULL);
	game->filelen = ft_strlen(argv[1]);
	if (game->filelen < 4 || ft_strncmp(&argv[1][game->filelen - 4], ".ber", 4) != 0)
		ft_error("File name must end with .ber", game);
	if (!is_mapfile_valid(game, argv[1]))
		ft_error("Invalid file format", game);
	get_map_dimensions(game, argv[1]);
	game->coins = 0;
	game->step = 0;
	game->frame = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Failed to initialize mlx.", game);
	if (game->col <= 0 || game->row <= 0)
		ft_error("Invalid window size.", game);
	game->win = mlx_new_window(game->mlx, (SIZE * game->col),
			(SIZE * game->row), "Game");
	free(game);
	return (0);
}
