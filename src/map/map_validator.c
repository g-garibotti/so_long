/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:58:26 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 18:31:36 by ggaribot         ###   ########.fr       */
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

bool	read_map(t_map *map, const char *filename)
{
	int		fd;
	char	*line;
	int		row;
	char	**temp_map;

	ft_printf("Debug: Opening map file\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFailed to open map file\n");
		return (false);
	}
	row = 0;
	temp_map = NULL;
	ft_printf("Debug: Reading map lines\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_printf("Debug: Read line %d: %s", row, line);
		if (row == 0)
			map->columns = ft_strlen(line) - 1;
		else if ((int)ft_strlen(line) - 1 != map->columns)
		{
			ft_printf("Error\nMap is not rectangular\n");
			free(line);
			close(fd);
			return (false);
		}
		ft_printf("Debug: Allocating memory for row %d\n", row);
		temp_map = realloc(temp_map, sizeof(char *) * (row + 1));
		if (!temp_map)
		{
			ft_printf("Error\nMemory allocation failed\n");
			free(line);
			close(fd);
			return (false);
		}
		ft_printf("Debug: Trimming line %d\n", row);
		temp_map[row] = ft_strtrim(line, "\n");
		if (!temp_map[row])
		{
			ft_printf("Error\nFailed to trim line\n");
			free(line);
			close(fd);
			return (false);
		}
		free(line);
		row++;
		ft_printf("Debug: Finished processing line %d\n", row - 1);
	}
	map->rows = row;
	map->map = temp_map;
	close(fd);
	ft_printf("Debug: Map read successfully. Rows: %d, Columns: %d\n",
		map->rows, map->columns);
	return (true);
}
