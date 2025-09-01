/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:53:49 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:07:24 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_player_on_tile(t_game *game, int x, int y)
{
	void	*on_box_img;

	if (game->map[y][x] == EXIT &&
		game->collectibles_collected >= game->collectibles_total)
	{
		on_box_img = mlx_xpm_file_to_image(game->mlx,
				"textures/on_box.xpm", &x, &y);
		if (on_box_img)
		{
			mlx_put_image_to_window(game->mlx, game->win, on_box_img,
				game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
			mlx_destroy_image(game->mlx, on_box_img);
		}
	}
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img_player,
			x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_single_tile(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor,
		x * TILE_SIZE, y * TILE_SIZE);
	if (game->map[y][x] != FLOOR)
		render_tile(game, x, y);
	if (x == game->player_x && y == game->player_y)
		render_player_on_tile(game, x, y);
}

void	render_game(t_game *game)
{
	int	x;
	int	y;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_single_tile(game, x, y);
			x++;
		}
		y++;
	}
}
