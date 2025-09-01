/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:52:15 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 14:52:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

int	validate_map(t_game *game)
{
	if (!check_rectangular_map(game))
		return (0);
	if (!check_map_walls(game))
		return (0);
	if (!check_map_elements(game))
		return (0);
	if (!check_valid_path(game))
		return (0);
	return (1);
}
