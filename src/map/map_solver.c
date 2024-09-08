/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:46:37 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 19:12:14 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void flood_fill(char **map, int x, int y, int *collectibles, bool *exit_reached)
{
    if (map[y][x] == '1' || map[y][x] == 'V')
        return;

    if (map[y][x] == 'C')
        (*collectibles)--;
    else if (map[y][x] == 'E')
        *exit_reached = true;

    map[y][x] = 'V';

    flood_fill(map, x + 1, y, collectibles, exit_reached);
    flood_fill(map, x - 1, y, collectibles, exit_reached);
    flood_fill(map, x, y + 1, collectibles, exit_reached);
    flood_fill(map, x, y - 1, collectibles, exit_reached);
}

bool is_map_solvable(t_map *map)
{
    char **temp_map;
    int i, collectibles;
    bool exit_reached = false;

    temp_map = malloc(sizeof(char *) * map->rows);
    if (!temp_map)
        return false;

    for (i = 0; i < map->rows; i++)
    {
        temp_map[i] = ft_strdup(map->map[i]);
        if (!temp_map[i])
        {
            while (--i >= 0)
                free(temp_map[i]);
            free(temp_map);
            return false;
        }
    }

    collectibles = map->collectibles;
    flood_fill(temp_map, map->player.x, map->player.y, &collectibles, &exit_reached);

    for (i = 0; i < map->rows; i++)
        free(temp_map[i]);
    free(temp_map);

    return (collectibles == 0 && exit_reached);
}
