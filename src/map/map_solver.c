/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:02:49 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 17:55:55 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	flood_fill(char **map, int x, int y, int *collectibles)
{
	if (map[y][x] == WALL || map[y][x] == 'V')
		return ;
	if (map[y][x] == COLLECTIBLE)
		(*collectibles)--;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, collectibles);
	flood_fill(map, x - 1, y, collectibles);
	flood_fill(map, x, y + 1, collectibles);
	flood_fill(map, x, y - 1, collectibles);
}

static int	find_player(t_map *map, int *x, int *y)
{
	*y = 0;
	while (*y < map->height)
	{
		*x = 0;
		while (*x < map->width)
		{
			if (map->grid[*y][*x] == PLAYER)
				return (1);
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

static int	check_exit_reachable(t_map *map, char **temp_map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == EXIT && temp_map[y][x] == 'V')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	is_map_solvable(t_map *map)
{
	int		x;
	int		y;
	int		collectibles;
	char	**temp_map;
	int		exit_reachable;

	collectibles = map->collectibles;
	temp_map = ft_strdup_2d(map->grid);
	if (!find_player(map, &x, &y))
	{
		ft_free_2d_array(temp_map);
		return (0);
	}
	flood_fill(temp_map, x, y, &collectibles);
	exit_reachable = check_exit_reachable(map, temp_map);
	ft_free_2d_array(temp_map);
	return (collectibles == 0 && exit_reachable);
}
