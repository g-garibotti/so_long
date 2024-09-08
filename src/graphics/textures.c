/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:12:11 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/08 16:12:24 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	load_image(t_game *game, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->position.x,
			&img->position.y);
	return (img->img != NULL);
}

static bool	load_player_images(t_game *game)
{
	if (!load_image(game, &game->player_images[PLAYER_FRONT],
			"assets/player_front.xpm"))
		return (false);
	if (!load_image(game, &game->player_images[PLAYER_BACK],
			"assets/player_back.xpm"))
		return (false);
	if (!load_image(game, &game->player_images[PLAYER_LEFT],
			"assets/player_left.xpm"))
		return (false);
	if (!load_image(game, &game->player_images[PLAYER_RIGHT],
			"assets/player_right.xpm"))
		return (false);
	return (true);
}

static bool	load_collectible_images(t_game *game)
{
	if (!load_image(game, &game->collectible_frames[0],
			"assets/collectible_1.xpm"))
		return (false);
	if (!load_image(game, &game->collectible_frames[1],
			"assets/collectible_2.xpm"))
		return (false);
	if (!load_image(game, &game->collectible_frames[2],
			"assets/collectible_3.xpm"))
		return (false);
	return (true);
}

bool	load_textures(t_game *game)
{
	if (!load_image(game, &game->wall, "assets/wall.xpm"))
		return (false);
	if (!load_image(game, &game->floor, "assets/floor.xpm"))
		return (false);
	if (!load_image(game, &game->exit, "assets/exit.xpm"))
		return (false);
	if (!load_player_images(game))
		return (false);
	if (!load_collectible_images(game))
		return (false);
	return (true);
}