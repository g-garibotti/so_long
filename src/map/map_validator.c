/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:26 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:36:36 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	check_horizontal_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->columns)
	{
		if (map->map[0][i] != WALL || map->map[map->rows - 1][i] != WALL)
			return (false);
		i++;
	}
	return (true);
}

static bool	check_vertical_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (map->map[i][0] != WALL || map->map[i][map->columns - 1] != WALL)
			return (false);
		i++;
	}
	return (true);
}

bool	is_surrounded_by_walls(t_map *map)
{
	return (check_horizontal_walls(map) && check_vertical_walls(map));
}
