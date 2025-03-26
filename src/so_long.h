/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:36:15 by davihako          #+#    #+#             */
/*   Updated: 2025/03/26 22:36:31 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_img
{
	void	*wall;
	void	*place;
	void	*player;
	void	*exit;
	void	*coin;
	void	*enemy;
	void	*player2;
}			t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		row;
	int		col;
	int		coins;
	int		total_coins;
	int		step;
	int		fd;
	int		players;
	int		exits;
	int		filelen;
	int		x_pos;
	int		y_pos;
	int		anim_frame;
	int		anim_counter;
	void	*player_frames[2];
	t_img	pics;
}			t_game;

/* Error handling */
void		ft_error(char *s, t_game *game);

void		get_map_dimensions(t_game *game, char *filename);
void		allocate_map(t_game *g, char *filename);
void		validate_map(t_game *game, char *filename);
int			is_mapfile_valid(t_game *game, char *filename);
/* Game controls */
int			key_hook(int keycode, t_game *game);
int			hook_up(t_game *game, int prow, int pcol);
int			hook_down(t_game *game, int prow, int pcol);
int			hook_left(t_game *game, int prow, int pcol);
int			hook_right(t_game *game, int prow, int pcol);

/* Rendering */
void		free_mlx_images(t_game *game);
void		do_stat(t_game *game, void *image, int y, int x);
int			render_loop(t_game *game);
void		free_animations(t_game *game);
void		ft_make_map(t_game *game);
void		update_animation(t_game *game);
void		render_step_counter(t_game *game);
void		get_xpm(t_game *game);
void		get_xpm2(t_game *game);

/* Player utils */
int			check_player_row(char **map, int rows);
int			check_player_col(char **map, int rows);
void		step_done(t_game *game);
void		free_var(t_game *game);

int			flood_fill(t_game *game, char **map_copy, int x, int y);
int			check_exit(t_game *game, char **map_copy, int x, int y);
char		**duplicate_map(t_game *game);
void		free_map_copy(char **arr, int j);

void		run_game_loop(t_game *game);
void		setup_hooks(t_game *game);
void		initialize_mlx(t_game *game);
t_game		*initialize_game(int argc, char **argv);

int			close_window(t_game *game);
int			mouse_hook(int keycode, t_game *game);

void		count_map_objects(t_game *game);
void		check_objects(t_game *game);
void		validate_arguments(int argc, char **argv, t_game *game);

#endif
