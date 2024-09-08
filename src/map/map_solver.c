/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:46:37 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 18:23:17 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	flood_fill(char **map, int x, int y, int *collectibles)
{
	if (map[y][x] == WALL || map[y][x] == 'V')
		return (false);
	if (map[y][x] == COLLECTIBLE)
		(*collectibles)--;
	else if (map[y][x] == EXIT)
		return (true);
	map[y][x] = 'V';
	return (flood_fill(map, x + 1, y, collectibles) || flood_fill(map, x - 1, y,
			collectibles) || flood_fill(map, x, y + 1, collectibles)
		|| flood_fill(map, x, y - 1, collectibles));
}

bool	is_map_solvable(t_map *map)
{
	char	**temp_map;
	bool	solvable;

	int i, collectibles;
	temp_map = malloc(sizeof(char *) * map->rows);
	if (!temp_map)
		return (false);
	for (i = 0; i < map->rows; i++)
	{
		temp_map[i] = ft_strdup(map->map[i]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (false);
		}
	}
	collectibles = map->collectibles;
	solvable = flood_fill(temp_map, map->player.x, map->player.y,
			&collectibles);
	for (i = 0; i < map->rows; i++)
		free(temp_map[i]);
	free(temp_map);
	return (solvable && collectibles == 0);
}
