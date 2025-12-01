/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:13:17 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/13 13:14:17 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		if (WTERMSIG(status) == SIGQUIT)
			return (131);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static void	child_process(char **argv, char **envp, char *cmd_path)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(cmd_path, argv, envp) == -1)
	{
		perror("execve");
		exit(126);
	}
}

int	execute_simple_cmd(char **argv, t_env_entry *env)
{
	char	*cmd_path;
	char	**envp;
	pid_t	pid;
	int		status;

	if (!argv || !argv[0])
		return (1);
	cmd_path = resolve_cmd_path(argv[0], env);
	if (!cmd_path)
	{
		write(STDERR_FILENO, argv[0], ft_strlen(argv[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		return (127);
	}
	envp = build_envp(env);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(cmd_path), free_envp(envp), 1);
	if (pid == 0)
		child_process(argv, envp, cmd_path);
	free(cmd_path);
	free_envp(envp);
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
