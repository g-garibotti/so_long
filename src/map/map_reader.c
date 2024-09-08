/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 21:37:24 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 22:06:00 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static size_t	get_effective_length(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		return (len - 1);
	return (len);
}

static bool	process_line(t_map *map, char *line, int row)
{
	size_t	effective_length;

	effective_length = get_effective_length(line);
	if (row == 0)
		map->columns = (int)effective_length;
	else if (effective_length != (size_t)map->columns)
	{
		ft_printf("Error: Map is not rectangular\n");
		return (false);
	}
	map->map[row] = ft_strtrim(line, "\n");
	if (!map->map[row])
	{
		ft_printf("Error: Failed to trim line\n");
		return (false);
	}
	return (true);
}

static bool	allocate_map(t_map *map, int fd)
{
	int		row_count;
	char	*line;

	row_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		row_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->map = (char **)malloc(sizeof(char *) * (row_count + 1));
	if (!map->map)
	{
		ft_printf("Error: Failed to allocate memory for map\n");
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
