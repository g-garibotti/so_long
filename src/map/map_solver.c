/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:02:49 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 14:03:11 by ggaribot         ###   ########.fr       */
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

int	is_map_solvable(t_map *map)
{
	int		x;
	int		y;
	int		collectibles;
	char	**temp_map;

	collectibles = map->collectibles;
	temp_map = ft_strdup_2d(map->grid);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (temp_map[y][x] == PLAYER)
			{
				flood_fill(temp_map, x, y, &collectibles);
				ft_free_2d_array(temp_map);
				return (collectibles == 0);
			}
			x++;
		}
		y++;
	}
	ft_free_2d_array(temp_map);
	return (0);
}
