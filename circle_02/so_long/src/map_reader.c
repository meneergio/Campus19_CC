/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:51:57 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 17:57:14 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	process_remaining_line(t_game *game, char *current_line,
	int line_pos, int *i)
{
	if (line_pos > 0)
	{
		current_line[line_pos] = '\0';
		if (!process_line(game, current_line, i))
			return (0);
	}
	return (1);
}

int	read_map_content(int fd, t_game *game)
{
	char	buffer[1024];
	char	current_line[256];
	int		positions[3];
	int		bytes_read;

	positions[0] = 0;
	positions[1] = 0;
	positions[2] = 0;
	bytes_read = read(fd, buffer + positions[0], 1);
	while (bytes_read > 0)
	{
		if (read_line_from_buffer(buffer, current_line, &positions[0],
				&positions[1]))
		{
			if (!process_line(game, current_line, &positions[2]))
				return (0);
		}
		bytes_read = read(fd, buffer + positions[0], 1);
	}
	if (!process_remaining_line(game, current_line, positions[1],
			&positions[2]))
		return (0);
	game->map_height = positions[2];
	return (1);
}
