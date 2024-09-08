/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:32:48 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 18:49:46 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include "../includes/so_long.h"

static bool	initialize_game(t_game *game, char *map_file)
{
	ft_printf("Debug: Entering initialize_game\n");
	ft_memset(game, 0, sizeof(t_game));
	game->current_collectible_frame = 0;
	ft_printf("Debug: Parsing map\n");
	if (!parse_map(game, map_file))
	{
		ft_printf("Error\nFailed to parse map\n");
		return (false);
	}
	ft_printf("Debug: Initializing MLX\n");
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize MLX\n");
		return (false);
	}
	ft_printf("Debug: Creating window\n");
	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "so_long");
	if (!game->win)
	{
		ft_printf("Error\nFailed to create window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (false);
	}
	ft_printf("Debug: Loading textures\n");
	if (!load_textures(game))
	{
		ft_printf("Error\nFailed to load textures\n");
		exit_game(game);
		return (false);
	}
	ft_printf("Debug: Game initialized successfully\n");
	return (true);
}

int main(int argc, char **argv)
{
    t_game game;

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
