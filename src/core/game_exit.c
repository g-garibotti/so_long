/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:55:03 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/10 15:17:49 by ggaribot         ###   ########.fr       */
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
			while (map->grid[i])
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
		mlx_destroy_image(mlx, textures->wall);
		mlx_destroy_image(mlx, textures->floor);
		mlx_destroy_image(mlx, textures->player);
		mlx_destroy_image(mlx, textures->exit);
		mlx_destroy_image(mlx, textures->enemy);
		mlx_destroy_image(mlx, textures->collectible[0]);
		mlx_destroy_image(mlx, textures->collectible[1]);
		mlx_destroy_image(mlx, textures->collectible[2]);
		free(textures);
	}
}

static void	free_mlx(t_mlx *mlx)
{
	if (mlx)
	{
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->mlx)
			mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		free(mlx);
	}
}

static void	free_game(t_game *game)
{
	if (game)
	{
		free_map(game->map);
		if (game->player)
			free(game->player);
		if (game->enemies)
			free(game->enemies);
		if (game->textures)
			free_textures(game->textures, game->mlx->mlx);
		free_mlx(game->mlx);
		free(game);
	}
}

void	free_and_exit(t_game *game, char *message)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	free_game(game);
	if (message)
	{
		ft_putstr_fd(message, 2);
		exit_status = EXIT_FAILURE;
	}
	exit(exit_status);
}
