/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:52:35 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:29:21 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	handle_movement_keys(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	move_player(game, new_x, new_y);
}

static int	is_movement_key(int keycode)
{
	return (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
		|| keycode == KEY_D || keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (game->game_won && keycode != KEY_ESC)
		return (0);
	if (keycode == KEY_ESC)
	{
		close_window(game);
		return (0);
	}
	if (is_movement_key(keycode))
		handle_movement_keys(keycode, game);
	return (0);
}
