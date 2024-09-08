/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:26:00 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:31:47 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	check_char(t_map *map, int i, int j, int *counts)
{
	char	c;

	c = map->map[i][j];
	if (c == PLAYER)
	{
		counts[0]++;
		map->player.x = j;
		map->player.y = i;
	}
	else if (c == EXIT)
	{
		counts[1]++;
		map->exit.x = j;
		map->exit.y = i;
	}
	else if (c == COLLECTIBLE)
		map->collectibles++;
	else if (c != WALL && c != FLOOR)
		return (false);
	return (true);
}

static bool	validate_counts(int player_count, int exit_count, int collectibles)
{
	if (player_count != 1)
	{
		ft_printf("Error: Map must contain exactly one player.\n");
		return (false);
	}
	if (exit_count != 1)
	{
		ft_printf("Error: Map must contain exactly one exit.\n");
		return (false);
	}
	if (collectibles == 0)
	{
		ft_printf("Error: Map must contain at least one collectible.\n");
		return (false);
	}
	return (true);
}

bool	validate_map_chars(t_map *map)
{
	int	counts[2];
	int	i;
	int	j;

	ft_memset(counts, 0, sizeof(counts));
	map->collectibles = 0;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->columns)
		{
			if (!check_char(map, i, j, counts))
			{
				ft_printf("Error: Invalid character at (%d, %d)\n", i, j);
				return (false);
			}
		}
	}
	return (validate_counts(counts[0], counts[1], map->collectibles));
}

static bool	allocate_map_memory(t_game *game)
{
	game->map.rows = 100;
	game->map.map = (char **)malloc(sizeof(char *) * game->map.rows);
	if (!game->map.map)
	{
		ft_printf("Error\nFailed to allocate memory for map\n");
		return (false);
	}
	return (true);
}

bool	parse_map(t_game *game, const char *filename)
{
	if (!filename || !*filename)
	{
		ft_printf("Error\nInvalid filename\n");
		return (false);
	}
	if (!allocate_map_memory(game) || !read_map(&game->map, filename)
		|| !validate_map_chars(&game->map)
		|| !is_surrounded_by_walls(&game->map) || !is_map_solvable(&game->map))
		return (false);
	game->window_width = game->map.columns * TILE_SIZE;
	game->window_height = game->map.rows * TILE_SIZE;
	if (game->window_width > MAX_WIDTH || game->window_height > MAX_HEIGHT)
	{
		ft_printf("Error\nMap is too large for the screen\n");
		return (false);
	}
	return (true);
}
