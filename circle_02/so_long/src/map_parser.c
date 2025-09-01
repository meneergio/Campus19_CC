/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:50:11 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/04 17:51:20 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	int		i;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				count++;
			i++;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	return (count);
}

char	**allocate_map(int height)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i <= height)
	{
		map[i] = NULL;
		i++;
	}
	return (map);
}

int	read_line_from_buffer(char *buffer, char *current_line,
	int *buffer_pos, int *line_pos)
{
	if (buffer[*buffer_pos] == '\n' || buffer[*buffer_pos] == '\0')
	{
		current_line[*line_pos] = '\0';
		if (*line_pos > 0)
		{
			*line_pos = 0;
			return (1);
		}
		*line_pos = 0;
		return (0);
	}
	current_line[*line_pos] = buffer[*buffer_pos];
	(*line_pos)++;
	*buffer_pos = 0;
	return (0);
}

int	process_line(t_game *game, char *current_line, int *i)
{
	game->map[*i] = ft_strdup(current_line);
	if (!game->map[*i])
		return (0);
	if (*i == 0)
		game->map_width = ft_strlen(current_line);
	(*i)++;
	return (1);
}
