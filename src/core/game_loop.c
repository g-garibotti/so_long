/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:05:49 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 21:40:45 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	key_press(int keycode, t_game *game)
{
	if (game->victory)
		return (0);
	if (keycode == KEY_ESC)
		mlx_loop_end(game->mlx);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
}

static void	update_collectible_frame(t_game *game)
{
	static int	frame_counter = 0;

	frame_counter++;
	if (frame_counter >= ANIMATION_SPEED)
	{
		game->current_collectible_frame = (game->current_collectible_frame + 1)
			% 3;
		frame_counter = 0;
	}
}

int	game_loop(t_game *game)
{
	if (game->victory)
	{
		ft_printf("Congratulations! You've won in %d moves!\n",
			game->movements);
		mlx_loop_end(game->mlx);
		return (1);
	}
	update_collectible_frame(game);
	render_game(game);
	return (0);
}
