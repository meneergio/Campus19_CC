/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:26:30 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/08 15:33:33 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	allocate_map_row(char **map_copy, t_game *game, int i)
{
	int	j;

	map_copy[i] = malloc(game->map_width + 1);
	if (!map_copy[i])
		return (0);
	j = 0;
	while (j < game->map_width)
	{
		map_copy[i][j] = game->map[i][j];
		j++;
	}
	map_copy[i][j] = '\0';
	return (1);
}

static void	free_partial_map(char **map_copy, int rows)
{
	while (--rows >= 0)
		free(map_copy[rows]);
	free(map_copy);
}

char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		if (!allocate_map_row(map_copy, game, i))
		{
			free_partial_map(map_copy, i);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

void	count_reachable_items(t_game *game, char **map_copy, t_validation *val)
{
	t_point	pos;

	val->collectibles_reachable = 0;
	val->exit_reachable = 0;
	pos.y = 0;
	while (pos.y < game->map_height)
	{
		pos.x = 0;
		while (pos.x < game->map_width)
		{
			if (game->map[pos.y][pos.x] == COLLECTIBLE
				&& map_copy[pos.y][pos.x] == 'V')
				val->collectibles_reachable++;
			else if (game->map[pos.y][pos.x] == EXIT
				&& map_copy[pos.y][pos.x] == 'V')
				val->exit_reachable = 1;
			pos.x++;
		}
		pos.y++;
	}
}

void	count_reachable_items_separate(t_game *game, char **collectible_map,
	char **exit_map, t_validation *val)
{
	t_point	pos;

	val->collectibles_reachable = 0;
	val->exit_reachable = 0;
	pos.y = 0;
	while (pos.y < game->map_height)
	{
		pos.x = 0;
		while (pos.x < game->map_width)
		{
			if (game->map[pos.y][pos.x] == COLLECTIBLE
				&& collectible_map[pos.y][pos.x] == 'V')
				val->collectibles_reachable++;
			else if (game->map[pos.y][pos.x] == EXIT
				&& exit_map[pos.y][pos.x] == 'V')
				val->exit_reachable = 1;
			pos.x++;
		}
		pos.y++;
	}
}
