/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:27:51 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 13:47:21 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	update_move_counter(t_game *game)
{
	game->player->moves++;
	render_game(game);
}

void	update_collectible_animation(t_game *game)
{
	game->current_collectible_frame = (game->current_collectible_frame + 1) % 3;
}

static int	check_collision(t_game *game, int new_x, int new_y)
{
	char	tile;

	tile = game->map->grid[new_y][new_x];
	if (tile == WALL)
		return (0);
	if (tile == ENEMY)
	{
		game->game_over = true;
		free_and_exit(game, "Game Over: You were caught by an enemy!\n");
		return (0);
	}
	if (tile == COLLECTIBLE)
		game->collected++;
	if (tile == EXIT && game->collected == game->map->collectibles)
	{
		game->game_over = true;
		free_and_exit(game, "Congratulations! You won the game!\n");
	}
	return (1);
}

void	update_player_position(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x + dx;
	new_y = game->player->y + dy;
	if (check_collision(game, new_x, new_y))
	{
		game->map->grid[game->player->y][game->player->x] = FLOOR;
		game->player->x = new_x;
		game->player->y = new_y;
		game->map->grid[new_y][new_x] = PLAYER;
		update_move_counter(game);
	}
}
