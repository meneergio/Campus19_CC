/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:55:04 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:02:48 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	can_move_to(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	if (game->map[y][x] == WALL)
		return (0);
	if (game->map[y][x] == EXIT &&
		game->collectibles_collected < game->collectibles_total)
		return (0);
	return (1);
}

void	collect_item(t_game *game, int x, int y)
{
	if (game->map[y][x] == COLLECTIBLE)
	{
		game->map[y][x] = FLOOR;
		game->collectibles_collected++;
		printf("💰 Collected! (%d/%d)\n",
			game->collectibles_collected, game->collectibles_total);
	}
}

void	check_win_condition(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == EXIT &&
		game->collectibles_collected >= game->collectibles_total)
	{
		game->game_won = 1;
		printf("🎉 Congratulations! You won in %d moves!\n", game->moves);
		printf("Press ESC or close window to exit.\n");
	}
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!can_move_to(game, new_x, new_y))
		return ;
	if (game->moves == 0)
		game->map[game->player_y][game->player_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	collect_item(game, new_x, new_y);
	check_win_condition(game);
	print_moves(game);
	render_game(game);
}
