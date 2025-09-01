/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:37:53 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:36:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}

static void	init_mlx_and_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_map(game->map);
		error_exit(ERR_MLX_INIT);
	}
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE,
			"So Long");
	if (!game->win)
	{
		cleanup_game(game);
		error_exit(ERR_MLX_WIN);
	}
}

static void	validate_and_parse_map(char *filename, t_game *game)
{
	if (!parse_map(filename, game))
		error_exit(ERR_MAP_FILE);
	if (!check_map_size(game))
	{
		free_map(game->map);
		error_exit(ERR_MAP_TOO_LARGE);
	}
	if (!validate_map(game))
	{
		free_map(game->map);
		error_exit(ERR_MAP_INVALID);
	}
}

static void	setup_game_elements(t_game *game)
{
	if (!load_textures(game))
	{
		cleanup_game(game);
		error_exit(ERR_MLX_IMG);
	}
	find_player_position(game);
	count_map_elements(game);
	render_game(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit(ERR_ARGS);
	init_game(&game);
	validate_and_parse_map(argv[1], &game);
	init_mlx_and_window(&game);
	setup_game_elements(&game);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	printf("🎮 So Long started!\n");
	printf("Use WASD or arrow keys to move\n");
	printf("Collect all %d items and reach the exit!\n",
		game.collectibles_total);
	mlx_loop(game.mlx);
	return (0);
}
