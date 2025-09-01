/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:51:05 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:37:31 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->exit_x = 0;
	game->exit_y = 0;
	game->collectibles_total = 0;
	game->collectibles_collected = 0;
	game->moves = 0;
	game->game_won = 0;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_player = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
}

static void	cleanup_images(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
}

void	cleanup_game(t_game *game)
{
	if (game->map)
		free_map(game->map);
	cleanup_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	close_window(t_game *game)
{
	printf("Game closed. Total moves: %d\n", game->moves);
	cleanup_game(game);
	exit(0);
	return (0);
}

int	check_map_size(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map_width * TILE_SIZE;
	window_height = game->map_height * TILE_SIZE;
	printf("Map dimensions: %dx%d tiles\n", game->map_width, game->map_height);
	printf("Required window size: %dx%d pixels\n", window_width, window_height);
	printf("Screen resolution: %dx%d pixels\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	printf("Maximum safe map size: %dx%d tiles\n", SAFE_MAX_WIDTH,
		SAFE_MAX_HEIGHT);
	if (game->map_width > SAFE_MAX_WIDTH || game->map_height > SAFE_MAX_HEIGHT)
		return (0);
	if (window_width >= SCREEN_WIDTH || window_height >= SCREEN_HEIGHT)
		return (0);
	printf("✓ Map size is valid for your screen\n");
	return (1);
}
