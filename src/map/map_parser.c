/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:26:00 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 18:43:50 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"


bool	validate_map_chars(t_map *map)
{
	int		player_count;
	int		exit_count;
	char	c;

	player_count = 0;
	exit_count = 0;
	int i, j;
	map->collectibles = 0;
	for (i = 0; i < map->rows; i++)
	{
		for (j = 0; j < map->columns; j++)
		{
			c = map->map[i][j];
			if (c == PLAYER)
			{
				player_count++;
				map->player.x = j;
				map->player.y = i;
			}
			else if (c == EXIT)
			{
				exit_count++;
				map->exit.x = j;
				map->exit.y = i;
			}
			else if (c == COLLECTIBLE)
				map->collectibles++;
			else if (c != WALL && c != FLOOR)
			{
				ft_printf("Error: Invalid character '%c' at position (%d, %d)\n", c, i, j);
				return (false);
			}
		}
	}
	if (player_count != 1)
	{
		ft_printf("Error: Map must contain exactly one player. Found %d.\n",
			player_count);
		return (false);
	}
	if (exit_count != 1)
	{
		ft_printf("Error: Map must contain exactly one exit. Found %d.\n",
			exit_count);
		return (false);
	}
	if (map->collectibles == 0)
	{
		ft_printf("Error: Map must contain at least one collectible.\n");
		return (false);
	}
	return (true);
}

bool	parse_map(t_game *game, const char *filename)
{
	ft_printf("Debug: Entering parse_map\n");
	if (!filename || !*filename)
	{
		ft_printf("Error\nInvalid filename\n");
		return (false);
	}
	// Allocate initial memory for the map
	ft_printf("Debug: Allocating initial memory for map\n");
	game->map.rows = 100; // Allocate space for up to 100 rows initially
	game->map.map = (char **)malloc(sizeof(char *) * game->map.rows);
	if (!game->map.map)
	{
		ft_printf("Error\nFailed to allocate memory for map\n");
		return (false);
	}
	ft_printf("Debug: Reading map\n");
	if (!read_map(&game->map, filename))
	{
		ft_printf("Error\nFailed to read map file or map is not rectangular\n");
		return (false);
	}
	ft_printf("Debug: Validating map characters\n");
	if (!validate_map_chars(&game->map))
	{
		ft_printf("Error\nInvalid map characters or wrong number of players/exits/collectibles\n");
		return (false);
	}
	ft_printf("Debug: Checking if map is surrounded by walls\n");
	if (!is_surrounded_by_walls(&game->map))
	{
		ft_printf("Error\nMap is not surrounded by walls\n");
		return (false);
	}
	game->window_width = game->map.columns * TILE_SIZE;
	game->window_height = game->map.rows * TILE_SIZE;
	ft_printf("Debug: Checking if map is solvable\n");
	if (!is_map_solvable(&game->map))
	{
		ft_printf("Error\nMap is not solvable\n");
		return (false);
	}
	if (game->window_width > MAX_WIDTH || game->window_height > MAX_HEIGHT)
	{
		ft_printf("Error\nMap is too large for the screen\n");
		return (false);
	}
	ft_printf("Debug: Map parsed successfully\n");
	return (true);
}
