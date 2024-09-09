/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:28:21 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 17:28:59 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	handle_enemy_collision(t_game *game)
{
	game->game_over = true;
	ft_printf("Game Over! You were caught by an enemy!\n");
	return (0);
}

static int	handle_collectible_collision(t_game *game, int new_x, int new_y)
{
	game->collected++;
	game->map->grid[new_y][new_x] = FLOOR;
	return (1);
}

static int	handle_exit_collision(t_game *game)
{
	if (game->collected == game->map->collectibles)
	{
		game->game_over = true;
		ft_printf("Congratulations! You won the game!\n");
		return (1);
	}
	ft_printf("You need to collect all items before exiting!\n");
	return (0);
}

int	check_collision(t_game *game, int new_x, int new_y)
{
	char	tile;

	tile = game->map->grid[new_y][new_x];
	if (tile == WALL)
		return (0);
	if (tile == ENEMY)
		return (handle_enemy_collision(game));
	if (tile == COLLECTIBLE)
		return (handle_collectible_collision(game, new_x, new_y));
	if (tile == EXIT)
		return (handle_exit_collision(game));
	return (1);
}
