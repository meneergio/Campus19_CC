/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:52:15 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/08 16:54:55 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	validate_map_content(t_game *game);
static int	has_duplicate_elements(t_game *game);
static int	has_invalid_characters(t_game *game);

static int	check_rectangular_map(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		if (ft_strlen(game->map[y]) != game->map_width)
			return (0);
		y++;
	}
	return (1);
}

static int	has_invalid_characters(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			c = game->map[y][x];
			if (c != WALL && c != FLOOR && c != PLAYER
				&& c != COLLECTIBLE && c != EXIT)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	has_duplicate_elements(t_game *game)
{
	int	x;
	int	y;
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == PLAYER)
				player_count++;
			else if (game->map[y][x] == EXIT)
				exit_count++;
			x++;
		}
		y++;
	}
	return (player_count > 1 || exit_count > 1);
}

static int	validate_map_content(t_game *game)
{
	if (!check_map_elements(game))
	{
		if (has_invalid_characters(game))
		{
			free_map(game->map);
			error_exit(ERR_MAP_INVALID_CHAR);
		}
		else if (has_duplicate_elements(game))
		{
			free_map(game->map);
			error_exit(ERR_MAP_TOO_MANY_PLAYERS);
		}
		else
		{
			free_map(game->map);
			error_exit(ERR_MAP_MISSING_ELEMENTS);
		}
	}
	if (!check_valid_path(game))
	{
		free_map(game->map);
		error_exit(ERR_MAP_NO_PATH);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_rectangular_map(game))
	{
		free_map(game->map);
		error_exit(ERR_MAP_NOT_RECTANGULAR);
	}
	if (!check_map_walls(game))
	{
		free_map(game->map);
		error_exit(ERR_MAP_NO_WALLS);
	}
	return (validate_map_content(game));
}
