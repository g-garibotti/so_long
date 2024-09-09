/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:30:03 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 14:59:48 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	set_player_position(t_player *player, int x, int y)
{
	player->x = x;
	player->y = y;
	player->direction = PLAYER_FRONT;
	player->moves = 0;
}

static t_player	*find_player_position(t_map *map)
{
	t_player	*player;
	int			x;
	int			y;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->grid[y][x] == PLAYER)
			{
				set_player_position(player, x, y);
				return (player);
			}
		}
	}
	free(player);
	return (NULL);
}

t_player	*init_player(t_map *map)
{
	return (find_player_position(map));
}

static void	set_enemy_position(t_enemy *enemy, int x, int y)
{
	enemy->x = x;
	enemy->y = y;
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
	y = -1;
	while (++y < map->height && count < map->enemies)
	{
		x = -1;
		while (++x < map->width && count < map->enemies)
		{
			if (map->grid[y][x] == ENEMY)
				set_enemy_position(&enemies[count++], x, y);
		}
	}
	return (enemies);
}
