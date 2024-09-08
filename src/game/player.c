/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:34 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:26:05 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	handle_collectible(t_game *game, int new_x, int new_y)
{
	game->map.collectibles--;
	game->map.map[new_y][new_x] = FLOOR;
}

static bool	handle_exit(t_game *game, int collectibles)
{
	if (collectibles == 0)
	{
		game->victory = true;
		return (true);
	}
	ft_printf("Collect all items before exiting!\n");
	return (false);
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map.map[game->map.player.y][game->map.player.x] = FLOOR;
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->map.map[new_y][new_x] = PLAYER;
	game->movements++;
}

void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	new_position;

	new_x = game->map.player.x + dx;
	new_y = game->map.player.y + dy;
	if (new_x < 0 || new_x >= game->map.columns || new_y < 0
		|| new_y >= game->map.rows)
		return ;
	new_position = game->map.map[new_y][new_x];
	if (new_position == WALL)
		return ;
	if (new_position == COLLECTIBLE)
		handle_collectible(game, new_x, new_y);
	if (new_position == EXIT)
		if (!handle_exit(game, game->map.collectibles))
			return ;
	update_player_position(game, new_x, new_y);
}
