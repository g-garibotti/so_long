/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:25:09 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 14:25:30 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	game_loop(t_game *game)
{
	static int	frame_count = 0;

	if (game->game_over)
		return (0);
	frame_count++;
	if (frame_count % ANIMATION_SPEED == 0)
		update_collectible_animation(game);
	if (frame_count % (ANIMATION_SPEED * 2) == 0)
		update_enemies(game);
	render_game(game);
	return (0);
}
