/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:07:18 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 19:58:31 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	draw_tile(t_game *game, int x, int y)
{
	char	tile;
	void	*img;

	tile = game->map.map[y][x];
	if (tile == WALL)
		img = game->wall.img;
	else if (tile == PLAYER)
		img = game->player_images[game->player_direction].img;
	else if (tile == COLLECTIBLE)
		img = game->collectible_frames[game->current_collectible_frame].img;
	else if (tile == EXIT)
		img = game->exit.img;
	else
		img = game->floor.img;
	mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y
		* TILE_SIZE);
}

static void	display_movement_count(t_game *game)
{
	char	*count_str;
	char	*display_str;

	count_str = ft_itoa(game->movements);
	if (!count_str)
		return ;
	display_str = ft_strjoin("Moves: ", count_str);
	if (!display_str)
	{
		free(count_str);
		return ;
	}
	mlx_string_put(game->mlx, game->win, 10, 20, 0x000000, display_str);
	free(count_str);
	free(display_str);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
	display_movement_count(game);
	if (game->victory)
	{
		mlx_string_put(game->mlx, game->win, game->window_width / 2 - 50,
			game->window_height / 2, 0x000000, "YOU WIN!");
	}
}
