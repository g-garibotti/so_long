/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:09:46 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 19:46:19 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	exit_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
		free(game->map.map[i++]);
	free(game->map.map);
	mlx_destroy_image(game->mlx, game->wall.img);
	mlx_destroy_image(game->mlx, game->floor.img);
	mlx_destroy_image(game->mlx, game->exit.img);
	i = 0;
	while (i < 3)
		mlx_destroy_image(game->mlx, game->collectible_frames[i++].img);
	i = 0;
	while (i < 4)
		mlx_destroy_image(game->mlx, game->player_images[i++].img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
