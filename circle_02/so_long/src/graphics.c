/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:52:00 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:35:08 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->img_wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &width, &height);
	game->img_floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &width, &height);
	game->img_player = mlx_xpm_file_to_image(game->mlx,
			"textures/cat.xpm", &width, &height);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/sushi.xpm", &width, &height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &width, &height);
	if (!game->img_wall || !game->img_floor || !game->img_player
		|| !game->img_collectible || !game->img_exit)
		return (0);
	return (1);
}

static void	*get_tile_image(t_game *game, char tile)
{
	if (tile == WALL)
		return (game->img_wall);
	else if (tile == FLOOR)
		return (game->img_floor);
	else if (tile == PLAYER)
		return (game->img_player);
	else if (tile == COLLECTIBLE)
		return (game->img_collectible);
	else if (tile == EXIT)
		return (game->img_exit);
	else
		return (game->img_floor);
}

void	render_tile(t_game *game, int x, int y)
{
	void	*img_to_draw;
	char	tile;

	tile = game->map[y][x];
	img_to_draw = get_tile_image(game, tile);
	if (img_to_draw)
		mlx_put_image_to_window(game->mlx, game->win, img_to_draw,
			x * TILE_SIZE, y * TILE_SIZE);
}
