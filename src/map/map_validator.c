/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:37:41 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 17:43:05 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	is_valid_char(char c)
{
	return (c == WALL || c == PLAYER || c == COLLECTIBLE || c == EXIT
		|| c == FLOOR || c == ENEMY);
}

int	check_valid_characters(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!is_valid_char(map->grid[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
