/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:37:24 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:50:02 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	process_line(t_map *map, char *line, int row)
{
	if (row == 0)
		map->columns = ft_strlen(line) - 1;
	else if ((int)ft_strlen(line) - 1 != map->columns)
	{
		ft_printf("Error\nMap is not rectangular\n");
		return (false);
	}
	map->map[row] = ft_strtrim(line, "\n");
	if (!map->map[row])
	{
		ft_printf("Error\nFailed to trim line\n");
		return (false);
	}
	return (true);
}

static bool	allocate_map(t_map *map, int fd)
{
	int	row_count;

	row_count = 0;
	while (get_next_line(fd))
		row_count++;
	close(fd);
	map->map = (char **)malloc(sizeof(char *) * (row_count + 1));
	if (!map->map)
	{
		ft_printf("Error\nFailed to allocate memory for map\n");
		return (false);
	}
	map->rows = row_count;
	return (true);
}

static void	free_map(t_map *map, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

bool	read_map(t_map *map, const char *filename)
{
	int		fd;
	char	*line;
	int		row;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || !allocate_map(map, fd))
		return (false);
	fd = open(filename, O_RDONLY);
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(map, line, row))
		{
			free(line);
			free_map(map, row);
			close(fd);
			return (false);
		}
		free(line);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
