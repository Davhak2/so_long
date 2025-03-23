#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include <stdio.h>

# define IMG_HEIGHT	32
# define IMG_WIDTH	32

# define WALL		'1'
# define FLOOR 		'0'
# define COINS  	'C'
# define PLAYER		'P'
# define MAP_EXIT 	'E'

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100

# define KEY_UP		65362
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_DOWN	65364

# define KEY_Q		113
# define KEY_ESC	65307

typedef enum s_directions
{
	FRONT = 1,
	LEFT,
	RIGHT,
	BACK
}	t_directions;

typedef struct s_position
{
	int	x;
	int	y;
}	t_positon;

typedef struct s_pics
{
	void	*(coll);
	void	*(player);
	void	*(player1);
	void	*(player2);
	void	*(player3);
	void	*(exit);
	void	*(exit1);
	void	*(wall);
	void	*(place);
	void	*(enemy);
}				t_pics;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	**mapc;
	int		row;
	int		col;
	int		coins;
	int		coins_lim;
	int		step;
	int		width;
	int		height;
	int		frame;
	int		fd;
	int		filelen;
	t_pics	pics;
}				t_game;

int	is_mapfile_valid(t_game *game, char *filename);

#endif
