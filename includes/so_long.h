/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:18:45 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 17:56:47 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/ft_printf.h"
# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080
# define PLAYER_FRONT 0
# define PLAYER_BACK 1
# define PLAYER_LEFT 2
# define PLAYER_RIGHT 3
# define FRAMES_PER_ANIMATION 40
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define FLOOR '0'
# define ENEMY 'N'
# define TILE_SIZE 32
# define EVENT_EXIT 17
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ANIMATION_SPEED 50

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			exits;
	int			players;
	int			enemies;
}				t_map;

typedef struct s_player
{
	int			x;
	int			y;
	int			direction;
	int			moves;
}				t_player;

typedef struct s_enemy
{
	int			x;
	int			y;
}				t_enemy;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*exit;
	void		*enemy;
	void		*collectible[3];
}				t_textures;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	t_enemy		*enemies;
	t_mlx		*mlx;
	t_textures	*textures;
	int			collected;
	bool		game_over;
	int			current_collectible_frame;
}				t_game;

void			free_and_exit(t_game *game, char *message);
int				load_textures(t_game *game);
void			render_game(t_game *game);
void			update_move_counter(t_game *game);
void			update_collectible_animation(t_game *game);
void			update_player_position(t_game *game, int dx, int dy);
void			update_enemies(t_game *game);
int				handle_key(int keycode, t_game *game);
int				game_loop(t_game *game);
t_map			*read_map(char *filename);
int				game_loop(t_game *game);
t_player		*init_player(t_map *map);
t_enemy			*init_enemies(t_map *map);
int				validate_map(t_map *map);
int				is_map_solvable(t_map *map);
int				check_collision(t_game *game, int new_x, int new_y);
int				check_valid_characters(t_map *map);
int				is_map_enclosed(t_map *map);

#endif