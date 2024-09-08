/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:32:48 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:26:38 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "so_long");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (false);
	}
	return (true);
}

static bool	initialize_game(t_game *game, char *map_file)
{
	ft_memset(game, 0, sizeof(t_game));
	if (!parse_map(game, map_file))
		return (false);
	if (!init_window(game))
		return (false);
	if (!load_textures(game))
	{
		exit_game(game);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	if (!initialize_game(&game, argv[1]))
	{
		ft_printf("Error\nFailed to initialize game\n");
		return (1);
	}
	setup_hooks(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	exit_game(&game);
	return (0);
}
