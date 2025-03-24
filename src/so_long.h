#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "../libft/libft.h"

# define SIZE 64
# define WALL '1'
# define FLOOR '0'
# define PLAYER 'P'
# define COINS 'C'
# define MAP_EXIT 'E'
# define ENEMY 'V'

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define IMG_WIDTH 64
# define IMG_HEIGHT 64

typedef struct s_img {
	void	*wall;
	void	*place;
	void	*player;
	void	*exit;
	void	*coin;
	void	*enemy;
}	t_img;

typedef struct s_game {
	void	*mlx;
	void	*win;
	char	**map;
	int		row;
	int		col;
	int		coins;
	int		total_coins;
	int		step;
	int		frame;
	int		fd;
	int		filelen;
	t_img	pics;
}	t_game;

// Error Handling
void	ft_error(char *s, t_game *game);

// Map Validation
void	get_map_dimensions(t_game *game, char *filename);
int		is_mapfile_valid(t_game *game, char *filename);
void	allocate_map(t_game *game, char *filename);

// Graphics
void	do_stat(t_game *game, void *image, int y, int x);
void	get_xpm(t_game *game);
void	ft_make_map(t_game *game);

// Movement
int		key_hook(int keycode, t_game *game);
int		hook_up(t_game *game, int prow, int pcol);
int		hook_down(t_game *game, int prow, int pcol);
int		hook_left(t_game *game, int prow, int pcol);
int		hook_right(t_game *game, int prow, int pcol);

// Utils
int		check_player_row(char **map, int rows);
int		check_player_col(char **map, int rows);
void	step_done(t_game *game);
void	free_var(t_game *game);

#endif
