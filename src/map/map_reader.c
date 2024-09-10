/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:17:19 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/10 11:08:52 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

static char	**read_map_lines(char *filename, int line_count)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	map = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (close(fd), map);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		line_count;
	int		i;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = read_map_lines(filename, line_count);
	if (!map->grid)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (map->grid[i] && map->grid[i][0] != '\0')
		i++;
	map->height = i;
	map->width = (i > 0) ? ft_strlen(map->grid[0]) : 0;
	return (map);
}
