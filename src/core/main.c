/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:16:02 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 15:06:59 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->map = NULL;
	game->player = NULL;
	game->enemies = NULL;
	game->mlx = NULL;
	game->textures = NULL;
	game->collected = 0;
	game->game_over = false;
	game->current_collectible_frame = 0;
	return (game);
}

static int	setup_mlx(t_game *game)
{
	game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!game->mlx)
	{
		ft_printf("Failed to allocate memory for MLX structure\n");
		return (0);
	}
	game->mlx->mlx = mlx_init();
	if (!game->mlx->mlx)
	{
		ft_printf("Failed to initialize MLX\n");
		return (0);
	}
	game->mlx->win = mlx_new_window(game->mlx->mlx, game->map->width
			* TILE_SIZE, game->map->height * TILE_SIZE, "so_long");
	if (!game->mlx->win)
	{
		ft_printf("Failed to create MLX window\n");
		return (0);
	}
	return (1);
}

static int	setup_game(t_game *game, char *map_file)
{
	game->map = read_map(map_file);
	if (!game->map || !validate_map(game->map) || !is_map_solvable(game->map))
	{
		free_and_exit(game, "Error: Invalid map\n");
		return (0);
	}
	if (!setup_mlx(game) || !load_textures(game))
	{
		free_and_exit(game,
			"Error: Failed to initialize MLX or load textures\n");
		return (0);
	}
	game->player = init_player(game->map);
	game->enemies = init_enemies(game->map);
	if (!game->player || !game->enemies)
	{
		free_and_exit(game, "Error: Failed to initialize player or enemies\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Error: Wrong number of arguments\n");
		return (1);
	}
	game = init_game();
	if (!game)
	{
		ft_printf("Error: Failed to initialize game\n");
		return (1);
	}
	if (!setup_game(game, argv[1]))
		return (1);
	mlx_hook(game->mlx->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->mlx->win, 17, 1L << 17, (int (*)())free_and_exit, game);
	mlx_loop_hook(game->mlx->mlx, game_loop, game);
	mlx_loop(game->mlx->mlx);
	free_and_exit(game, NULL);
	return (0);
}
