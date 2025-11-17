/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:34:52 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/12 21:12:15 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// helper functie om de input voor 1 heredoc te lezen
static int	read_heredoc_input(const char *delimiter, int hdoc_fd_write, 
                                t_env_entry *env)
{
	char	*line;
	char	*expanded;
	size_t	delim_len;

	delim_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");

		// 1. EOF (Ctrl+D) of fout gedetecteerd
		if (!line)
			return (0);

		// 2. Delimiter gevonden: Stop met lezen
		if (ft_strncmp(line, delimiter, delim_len) == 0 && line[delim_len] == '\0')
		{
			free(line);
			return (0);
		}

		// 3. EXPAND VARIABLES in de regel
		expanded = expand_word_all(line, env);
		free(line);
		
		// 4. Schrijf de ge-expanded regel naar de pipe
		if (expanded)
		{
			write(hdoc_fd_write, expanded, ft_strlen(expanded));
			write(hdoc_fd_write, "\n", 1);
			free(expanded);
		}
		else
		{
			write(hdoc_fd_write, "\n", 1);
		}
	}
}

// prepare heredocs voor alle commands in de AST
int	prepare_heredocs(t_ast *ast, t_env_entry *env, int last_status)
{
	int		i;
	t_redir	*r;
	int		pipe_fds[2];

	(void)last_status;  // Niet nodig voor nu
	if (!ast || !ast->cmdv)
		return (1);
	i = 0;
	while (i < ast->ncmd)
	{
		r = ast->cmdv[i].redirs;
		while (r)
		{
			if (r->type == R_HEREDOC)
			{
				// 1. Maak een pipe aan
				if (pipe(pipe_fds) < 0)
				{
					perror("minishell: pipe failed");
					return (0);
				}

				r->hdoc_fd = pipe_fds[0];

				// 2. Lees de input EN EXPAND VARIABLES
				if (read_heredoc_input(r->arg, pipe_fds[1], env) != 0)
				{
					close(pipe_fds[0]);
					close(pipe_fds[1]);
					r->hdoc_fd = -1;
					return (0);
				}

				// 3. Sluit schrijf-zijde
				close(pipe_fds[1]);
			}
			r = r->next;
		}
		i++;
	}
	return (1);
}
