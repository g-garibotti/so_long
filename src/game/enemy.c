/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:41:54 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 13:46:14 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	is_valid_move(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
		return (0);
	return (game->map->grid[y][x] == FLOOR);
}

static void	get_random_direction(int *dx, int *dy)
{
	int	direction;

	direction = rand() % 4;
	*dx = 0;
	*dy = 0;
	if (direction == 0)
		*dx = -1;
	else if (direction == 1)
		*dx = 1;
	else if (direction == 2)
		*dy = -1;
	else
		*dy = 1;
}

static void	move_enemy(t_game *game, int index)
{
	int	dx;
	int	dy;
	int	new_x;
	int	new_y;

	get_random_direction(&dx, &dy);
	new_x = game->enemies[index].x + dx;
	new_y = game->enemies[index].y + dy;
	if (is_valid_move(game, new_x, new_y))
	{
		game->map->grid[game->enemies[index].y][game->enemies[index].x] = FLOOR;
		game->enemies[index].x = new_x;
		game->enemies[index].y = new_y;
		game->map->grid[new_y][new_x] = ENEMY;
	}
}

void	update_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->enemies)
	{
		move_enemy(game, i);
		i++;
	}
}
