/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:34 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 19:59:43 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void move_player(t_game *game, int dx, int dy)
{
    int new_x = game->map.player.x + dx;
    int new_y = game->map.player.y + dy;

    if (new_x < 0 || new_x >= game->map.columns || new_y < 0 || new_y >= game->map.rows)
        return;

    char new_position = game->map.map[new_y][new_x];

    if (new_position == WALL)
        return;

    if (new_position == COLLECTIBLE)
    {
        game->map.collectibles--;
        game->map.map[new_y][new_x] = FLOOR;
    }

    if (new_position == EXIT && game->map.collectibles == 0)
        game->victory = true;
    else if (new_position == EXIT)
    {
        ft_printf("Collect all items before exiting!\n");
        return;
    }

    game->map.map[game->map.player.y][game->map.player.x] = FLOOR;
    game->map.player.x = new_x;
    game->map.player.y = new_y;
    game->map.map[new_y][new_x] = PLAYER;
    game->movements++;
}
