/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:55:03 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 14:40:23 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->grid)
		{
			i = 0;
			while (i < map->height)
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
		}
		free(map);
	}
}

static void	free_textures(t_textures *textures, void *mlx)
{
	if (textures)
	{
		if (textures->wall)
			mlx_destroy_image(mlx, textures->wall);
		if (textures->floor)
			mlx_destroy_image(mlx, textures->floor);
		if (textures->player)
			mlx_destroy_image(mlx, textures->player);
		if (textures->exit)
			mlx_destroy_image(mlx, textures->exit);
		if (textures->enemy)
			mlx_destroy_image(mlx, textures->enemy);
		if (textures->collectible[0])
			mlx_destroy_image(mlx, textures->collectible[0]);
		if (textures->collectible[1])
			mlx_destroy_image(mlx, textures->collectible[1]);
		if (textures->collectible[2])
			mlx_destroy_image(mlx, textures->collectible[2]);
		free(textures);
	}
}

void	free_and_exit(t_game *game, char *message)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->player)
			free(game->player);
		if (game->enemies)
			free(game->enemies);
		if (game->mlx)
		{
			if (game->textures)
				free_textures(game->textures, game->mlx->mlx);
			if (game->mlx->win)
				mlx_destroy_window(game->mlx->mlx, game->mlx->win);
			if (game->mlx->mlx)
				mlx_destroy_display(game->mlx->mlx);
			free(game->mlx->mlx);
			free(game->mlx);
		}
		free(game);
	}
	if (message)
		ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}
