/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:55:07 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/19 17:40:27 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern void	setup_prompt_signal_handlers(void);

// Checkt of de enige command een geldige builtin is
static int	is_single_builtin(t_ast *ast)
{
	if (!ast->cmdv[0].argv)
		return (0);
	if (!ast->cmdv[0].argv[0])
		return (0);
	if (!is_builtin(ast->cmdv[0].argv[0]))
		return (0);
	return (1);
}

// Herstelt een eerder opgeslagen file descriptor
static void	restore_fd(int saved_fd, int target_fd)
{
	if (saved_fd == -1)
		return ;
	dup2(saved_fd, target_fd);
	close(saved_fd);
}

// Voert een enkel builtin-commando uit in de parent (met redirs)
static int	exec_single_builtin(t_ast *ast, t_env_entry **env, int *last_status)
{
	int	orig_in;
	int	orig_out;
	int	is_exit_builtin;

	orig_in = -1;
	orig_out = -1;
	if (!is_single_builtin(ast))
		return (0);
	is_exit_builtin = (ft_strncmp(ast->cmdv[0].argv[0], "exit", 4) == 0
			&& ast->cmdv[0].argv[0][4] == '\0');
	if (!is_exit_builtin)
	{
		orig_in = dup(STDIN_FILENO);
		orig_out = dup(STDOUT_FILENO);
	}
	if (apply_redirs(ast->cmdv[0].redirs) == 0)
		*last_status = run_builtin(ast->cmdv[0].argv, env, *last_status);
	else
		*last_status = 1;
	if (!is_exit_builtin)
	{
		restore_fd(orig_in, STDIN_FILENO);
		restore_fd(orig_out, STDOUT_FILENO);
	}
	return (1);
}

// Voert een enkel extern commando uit via fork + execve
static int	exec_single_external(t_ast *ast, t_env_entry **env,
			int *last_status)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (apply_redirs(ast->cmdv[0].redirs) == 0)
			execute_external_cmd(&ast->cmdv[0], env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	handle_child_status(status, last_status);
	setup_prompt_signal_handlers();
	return (0);
}

// Dispatch voor één commando: builtin in parent, extern in child
int	execute_single(t_ast *ast, t_env_entry **env, int *last_status)
{
	if (!ast->cmdv[0].argv || !ast->cmdv[0].argv[0])
		return (0);
	if (is_builtin(ast->cmdv[0].argv[0]))
		return (exec_single_builtin(ast, env, last_status));
	return (exec_single_external(ast, env, last_status));
}
