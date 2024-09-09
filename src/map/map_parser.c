/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:58:53 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 13:59:20 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	count_map_elements(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == PLAYER)
				map->players++;
			else if (map->grid[y][x] == COLLECTIBLE)
				map->collectibles++;
			else if (map->grid[y][x] == EXIT)
				map->exits++;
			else if (map->grid[y][x] == ENEMY)
				map->enemies++;
			x++;
		}
		y++;
	}
	return (map->players == 1 && map->collectibles >= 1 && map->exits == 1);
}

static int	is_map_rectangular(t_map *map)
{
	int		y;
	size_t	len;

	y = 0;
	len = ft_strlen(map->grid[0]);
	while (y < map->height)
	{
		if (ft_strlen(map->grid[y]) != len)
			return (0);
		y++;
	}
	map->width = len;
	return (1);
}

static int	is_map_enclosed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((y == 0 || y == map->height - 1 || x == 0 || x == map->width
					- 1) && map->grid[y][x] != WALL)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!is_map_rectangular(map))
		return (0);
	if (!is_map_enclosed(map))
		return (0);
	if (!count_map_elements(map))
		return (0);
	return (1);
}
