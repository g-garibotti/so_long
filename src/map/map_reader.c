/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:17:19 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/10 13:16:34 by ggaribot         ###   ########.fr       */
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

static void	trim_newline(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

static int	process_line(char **map, int *i, char *line)
{
	trim_newline(line);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (0);
	}
	map[(*i)++] = line;
	return (1);
}

static char	**read_map_lines(char *filename, int line_count)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	map = (char **)ft_calloc(line_count + 1, sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(map), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!process_line(map, &i, line))
		{
			ft_free_2d_array(map);
			close(fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		line_count;

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
	return (map);
}
