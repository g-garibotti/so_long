/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:18:45 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 18:50:56 by ggaribot         ###   ########.fr       */
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
# define SPEED_MOVEMENT_ENEMY 70
# define FRAMES_PER_ANIMATION 40
# define WALL '1'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define FLOOR '0'
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

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	t_position	player;
	t_position	exit;
	int			collectibles;
}				t_map;

typedef struct s_player
{
	t_position	position;
	int			moves;
}				t_player;

typedef struct s_enemy
{
	t_position	position;
	int			direction;
	bool		is_vertical;
}				t_enemy;

typedef struct s_image
{
	void		*img;
	t_position	position;
}				t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			window_width;
	int			window_height;
	int			movements;
	bool		victory;
	t_map		map;
	t_enemy		enemy;
	t_image		enemy_img;
	t_image		floor;
	t_image		wall;
	t_image		collectible_frames[3];
	t_image		exit;
	t_image		player_images[4];
	int			current_collectible_frame;
	int			player_direction;
}				t_game;

// Function prototypes

// Core functions
void			setup_hooks(t_game *game);
int				game_loop(t_game *game);
void			exit_game(t_game *game);

// Map functions
bool			parse_map(t_game *game, const char *filename);
bool			validate_map_chars(t_map *map);
bool			is_surrounded_by_walls(t_map *map);
bool			read_map(t_map *map, const char *filename);
bool			is_map_solvable(t_map *map);

// Player functions
void			move_player(t_game *game, int dx, int dy);

// Graphics functions
bool			load_textures(t_game *game);
void			render_game(t_game *game);

#endif