/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:46:37 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:47:12 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	flood_fill_recursive(char **map, t_position pos, int *collectibles,
		bool *exit_reached)
{
	t_position	next_pos;

	if (map[pos.y][pos.x] == WALL || map[pos.y][pos.x] == 'V')
		return ;
	if (map[pos.y][pos.x] == COLLECTIBLE)
		(*collectibles)--;
	else if (map[pos.y][pos.x] == EXIT)
		*exit_reached = true;
	map[pos.y][pos.x] = 'V';
	next_pos = (t_position){pos.x + 1, pos.y};
	flood_fill_recursive(map, next_pos, collectibles, exit_reached);
	next_pos = (t_position){pos.x - 1, pos.y};
	flood_fill_recursive(map, next_pos, collectibles, exit_reached);
	next_pos = (t_position){pos.x, pos.y + 1};
	flood_fill_recursive(map, next_pos, collectibles, exit_reached);
	next_pos = (t_position){pos.x, pos.y - 1};
	flood_fill_recursive(map, next_pos, collectibles, exit_reached);
}

static void	flood_fill(char **map, t_position start, int *collectibles,
		bool *exit_reached)
{
	flood_fill_recursive(map, start, collectibles, exit_reached);
}

static char	**create_temp_map(t_map *map)
{
	char	**temp_map;
	int		i;

	temp_map = malloc(sizeof(char *) * map->rows);
	if (!temp_map)
		return (NULL);
	i = 0;
	while (i < map->rows)
	{
		temp_map[i] = ft_strdup(map->map[i]);
		if (!temp_map[i])
		{
			while (--i >= 0)
				free(temp_map[i]);
			free(temp_map);
			return (NULL);
		}
		i++;
	}
	return (temp_map);
}

static void	free_temp_map(char **temp_map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(temp_map[i]);
		i++;
	}
	free(temp_map);
}

bool	is_map_solvable(t_map *map)
{
	char	**temp_map;
	bool	exit_reached;
	int		collectibles;

	temp_map = create_temp_map(map);
	if (!temp_map)
		return (false);
	exit_reached = false;
	collectibles = map->collectibles;
	flood_fill(temp_map, map->player, &collectibles, &exit_reached);
	free_temp_map(temp_map, map->rows);
	return (collectibles == 0 && exit_reached);
}
