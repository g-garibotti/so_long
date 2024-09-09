/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:25:15 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 13:34:54 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	draw_tile(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, img, x * TILE_SIZE,
		y * TILE_SIZE);
}

static void	draw_move_counter(t_game *game)
{
	char	*moves_str;
	char	*display_str;

	moves_str = ft_itoa(game->player->moves);
	display_str = ft_strjoin("Moves: ", moves_str);
	mlx_string_put(game->mlx->mlx, game->mlx->win, 10, 20, 0x000000,
		display_str);
	free(moves_str);
	free(display_str);
}

static void	draw_map_tile(t_game *game, int x, int y)
{
	draw_tile(game, game->textures->floor, x, y);
	if (game->map->grid[y][x] == WALL)
		draw_tile(game, game->textures->wall, x, y);
	else if (game->map->grid[y][x] == PLAYER)
		draw_tile(game, game->textures->player, x, y);
	else if (game->map->grid[y][x] == COLLECTIBLE)
		draw_tile(game,
			game->textures->collectible[game->current_collectible_frame], x, y);
	else if (game->map->grid[y][x] == EXIT)
		draw_tile(game, game->textures->exit, x, y);
	else if (game->map->grid[y][x] == ENEMY)
		draw_tile(game, game->textures->enemy, x, y);
}

static void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			draw_map_tile(game, x, y);
			x++;
		}
		y++;
	}
}

void	render_game(t_game *game)
{
	draw_map(game);
	draw_move_counter(game);
}
