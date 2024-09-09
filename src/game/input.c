/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:41 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 13:55:01 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_and_exit(game, "Game closed by user.\n");
	else if (keycode == KEY_W || keycode == KEY_UP)
		update_player_position(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		update_player_position(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		update_player_position(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		update_player_position(game, 1, 0);
	return (0);
}
