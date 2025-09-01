/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:55:24 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 15:16:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	parse_map(char *filename, t_game *game)
{
	int	fd;

	game->map_height = count_lines(filename);
	if (game->map_height == 0)
		return (0);
	game->map = allocate_map(game->map_height);
	if (!game->map)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map);
		return (0);
	}
	if (!read_map_content(fd, game))
	{
		free_map(game->map);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	check_horizontal_walls(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[y][x] != WALL)
			return (0);
		x++;
	}
	return (1);
}

int	check_map_walls(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		if (y == 0 || y == game->map_height - 1)
		{
			if (!check_horizontal_walls(game, y))
				return (0);
		}
		else
		{
			if (game->map[y][0] != WALL ||
				game->map[y][game->map_width - 1] != WALL)
				return (0);
		}
		y++;
	}
	return (1);
}

static void	count_elements(t_game *game, int x, int y, int *counts)
{
	char	c;

	c = game->map[y][x];
	if (c == PLAYER)
		counts[0]++;
	else if (c == EXIT)
		counts[1]++;
	else if (c == COLLECTIBLE)
		counts[2]++;
	else if (c != WALL && c != FLOOR)
		counts[3] = 1;
}

int	check_map_elements(t_game *game)
{
	int	x;
	int	y;
	int	counts[4];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			count_elements(game, x, y, counts);
			x++;
		}
		y++;
	}
	if (counts[3] == 1)
		return (0);
	return (counts[0] == 1 && counts[1] == 1 && counts[2] >= 1);
}
