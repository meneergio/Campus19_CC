/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:41:07 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/25 14:30:11 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// wacht op heredoc-proces en handelt opruimen/status af
static int	heredoc_wait_and_cleanup(pid_t pid, int read_fd, t_redir *r)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	terminal_restore_control_chars();
	tcflush(STDIN_FILENO, TCIFLUSH);
	setup_prompt_signal_handlers();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		close(read_fd);
		r->hdoc_fd = -1;
		g_exit_status = 130;
		return (0);
	}
	r->hdoc_fd = read_fd;
	return (1);
}

// Sluit alle geërfde file descriptors behalve de pipe write-end
static void	close_inherited_fds(int keep_fd)
{
	int	fd;

	fd = 3;
	while (fd < 256)
	{
		if (fd != keep_fd)
			close(fd);
		fd++;
	}
}

// Logica voor het kindproces dat de heredoc-input leest
static void	heredoc_child_process(int fds0, int fds1,
	t_redir *r, t_env_entry *env)
{
	close(fds0);
	close_inherited_fds(fds1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	read_heredoc_input(r->arg, fds1, env);
	close(fds1);
	exit(0);
}

// maak pipe en vul hdoc_fd voor 1 heredoc-redir
int	handle_one_heredoc(t_redir *r, t_env_entry *env)
{
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) < 0)
	{
		perror("minishell: pipe failed");
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failed");
		close(fds[0]);
		close(fds[1]);
		return (0);
	}
	if (pid == 0)
		heredoc_child_process(fds[0], fds[1], r, env);
	close(fds[1]);
	return (heredoc_wait_and_cleanup(pid, fds[0], r));
}

// prepare heredocs voor alle commands in de AST
int	prepare_heredocs(t_ast *ast, t_env_entry *env, int last_status)
{
	int	i;

	(void)last_status;
	if (!ast || !ast->cmdv)
		return (1);
	i = 0;
	while (i < ast->ncmd)
	{
		if (!prepare_heredocs_one_cmd(ast->cmdv[i].redirs, env))
		{
			cleanup_opened_heredocs(ast, i);
			return (0);
		}
		i++;
	}
	return (1);
}
