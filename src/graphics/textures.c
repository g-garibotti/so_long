/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:21:56 by ggaribot          #+#    #+#             */
/*   Updated: 2024/09/09 14:56:35 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	*load_xpm(void *mlx, char *path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!img)
		ft_printf("Failed to load texture: %s\n", path);
	return (img);
}

int	load_textures(t_game *game)
{
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return (0);
	game->textures->wall = load_xpm(game->mlx->mlx, "assets/wall.xpm");
	game->textures->floor = load_xpm(game->mlx->mlx, "assets/floor.xpm");
	game->textures->player = load_xpm(game->mlx->mlx, "assets/player.xpm");
	game->textures->exit = load_xpm(game->mlx->mlx, "assets/exit.xpm");
	game->textures->enemy = load_xpm(game->mlx->mlx, "assets/enemy.xpm");
	game->textures->collectible[0] = load_xpm(game->mlx->mlx,
			"assets/collectible_1.xpm");
	game->textures->collectible[1] = load_xpm(game->mlx->mlx,
			"assets/collectible_2.xpm");
	game->textures->collectible[2] = load_xpm(game->mlx->mlx,
			"assets/collectible_3.xpm");
	if (!game->textures->wall || !game->textures->floor
		|| !game->textures->player || !game->textures->exit
		|| !game->textures->enemy || !game->textures->collectible[0]
		|| !game->textures->collectible[1] || !game->textures->collectible[2])
	{
		ft_printf("Error: Failed to load one or more textures\n");
		return (0);
	}
	return (1);
}
