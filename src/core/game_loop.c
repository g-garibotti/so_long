/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:25:09 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 15:08:59 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	game_loop(t_game *game)
{
	static int	frame_count = 0;
	static int	end_message_printed = 0;

	if (game->game_over && !end_message_printed)
	{
		ft_printf("Total moves: %d\n", game->player->moves);
		end_message_printed = 1;
		mlx_loop_end(game->mlx->mlx);
		return (1);
	}
	frame_count++;
	if (frame_count % ANIMATION_SPEED == 0)
		update_collectible_animation(game);
	if (frame_count % (ANIMATION_SPEED * 2) == 0)
		update_enemies(game);
	render_game(game);
	return (0);
}
