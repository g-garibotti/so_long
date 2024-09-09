/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:30:03 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 14:30:23 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_player	*init_player(t_map *map)
{
	t_player	*player;
	int			x;
	int			y;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == PLAYER)
			{
				player->x = x;
				player->y = y;
				player->direction = PLAYER_FRONT;
				player->moves = 0;
				return (player);
			}
			x++;
		}
		y++;
	}
	free(player);
	return (NULL);
}

t_enemy	*init_enemies(t_map *map)
{
	t_enemy	*enemies;
	int		x;
	int		y;
	int		count;

	enemies = (t_enemy *)malloc(sizeof(t_enemy) * map->enemies);
	if (!enemies)
		return (NULL);
	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == ENEMY)
			{
				enemies[count].x = x;
				enemies[count].y = y;
				count++;
			}
			x++;
		}
		y++;
	}
	return (enemies);
}
