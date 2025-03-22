#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"

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

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			columns;
	int			coins;
	int			exit;
	int			players;
	t_positon	player;
}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			movements;
	int			player_sprite;
	int			fd;
	t_map		map;
	t_image		wall;
	t_image		floor;
	t_image		coins;
	t_image		open_exit;
	t_image		exit_closed;
	t_image		front;
	t_image		left;
	t_image		right;
	t_image		back;
}	t_game;

#endif
