/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:40:33 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/26 15:21:52 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// schrijf 1 heredoc-lijn met of zonder expansie
static void	heredoc_write_one(const char *line, int fd,
							t_env_entry *env, int no_expand)
{
	char	*expanded;

	if (no_expand)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		return ;
	}
	expanded = expand_word_all(line, env);
	if (!expanded)
	{
		write(fd, "\n", 1);
		return ;
	}
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
}

// toon warning bij EOF vóór delimiter (Ctrl-D in heredoc)
static void	heredoc_eof_warning(const char *delim)
{
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted '", 2);
	ft_putstr_fd((char *)delim, 2);
	ft_putstr_fd("')\n", 2);
}

// Lees een regel met raw read() - veiliger dan readline in child
static char	*read_line_raw(void)
{
	char	buffer[1024];
	int		i;
	int		n;

	i = 0;
	write(STDOUT_FILENO, "> ", 2);
	while (i < 1023)
	{
		n = read(STDIN_FILENO, &buffer[i], 1);
		if (n <= 0)
			return (NULL);
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			return (ft_strdup(buffer));
		}
		i++;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

// leest alle regels voor 1 heredoc, met of zonder expansie
int	read_heredoc_input(const char *delim, int hdoc_fd_write,
					t_env_entry *env, int no_expand)
{
	char	*line;
	size_t	delim_len;

	delim_len = ft_strlen(delim);
	while (1)
	{
		line = read_line_raw();
		if (!line)
		{
			heredoc_eof_warning(delim);
			close(hdoc_fd_write);
			return (0);
		}
		if (ft_strncmp(line, delim, delim_len) == 0
			&& line[delim_len] == '\0')
		{
			free(line);
			break ;
		}
		heredoc_write_one(line, hdoc_fd_write, env, no_expand);
		free(line);
	}
	close(hdoc_fd_write);
	return (0);
}
