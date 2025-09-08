/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:51:19 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/08 16:18:04 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	flood_fill(char **map_copy, t_point pos, t_game *game)
{
	if (pos.x < 0 || pos.x >= game->map_width)
		return ;
	if (pos.y < 0 || pos.y >= game->map_height)
		return ;
	if (map_copy[pos.y][pos.x] == WALL || map_copy[pos.y][pos.x] == 'V'
		|| map_copy[pos.y][pos.x] == EXIT)
		return ;
	map_copy[pos.y][pos.x] = 'V';
	flood_fill(map_copy, (t_point){pos.x + 1, pos.y}, game);
	flood_fill(map_copy, (t_point){pos.x - 1, pos.y}, game);
	flood_fill(map_copy, (t_point){pos.x, pos.y + 1}, game);
	flood_fill(map_copy, (t_point){pos.x, pos.y - 1}, game);
}

static void	process_map_cell(t_game *game, t_point pos, t_validation *val)
{
	if (game->map[pos.y][pos.x] == PLAYER)
	{
		val->player_pos.x = pos.x;
		val->player_pos.y = pos.y;
	}
	else if (game->map[pos.y][pos.x] == COLLECTIBLE)
		val->total_collectibles++;
}

static void	find_player_and_count_collectibles(t_game *game, t_validation *val)
{
	t_point	pos;

	val->player_pos.x = -1;
	val->total_collectibles = 0;
	pos.y = 0;
	while (pos.y < game->map_height)
	{
		pos.x = 0;
		while (pos.x < game->map_width)
		{
			process_map_cell(game, pos, val);
			pos.x++;
		}
		pos.y++;
	}
}

int	check_valid_path(t_game *game)
{
	char			**map_copy;
	t_validation	val;

	find_player_and_count_collectibles(game, &val);
	if (val.player_pos.x == -1)
		return (0);
	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	flood_fill(map_copy, val.player_pos, game);
	count_reachable_items(game, map_copy, &val);
	free_map(map_copy);
	return (val.collectibles_reachable == val.total_collectibles);
}
