/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:55:07 by dzotti            #+#    #+#             */
/*   Updated: 2025/12/01 18:42:10 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Functies in execute_single_utils.c:
int		is_single_builtin(t_ast *ast);
void	restore_fd(int saved_fd, int target_fd);
int		wait_and_handle_external(pid_t pid, int *last_status);

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
		*last_status = run_builtin(ast->cmdv[0].argv, env, *last_status, ast);
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

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	terminal_restore_control_chars();
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (apply_redirs(ast->cmdv[0].redirs) == 0)
		{
			close_all_heredoc_fds(ast);
			execute_external_cmd(&ast->cmdv[0], env);
		}
		exit(1);
	}
	return (wait_and_handle_external(pid, last_status));
}

// Dispatch voor één commando: builtin in parent, extern in child
int	execute_single(t_ast *ast, t_env_entry **env, int *last_status)
{
	if (!ast->cmdv[0].argv || !ast->cmdv[0].argv[0])
		return (handle_empty_redirect(ast->cmdv[0].redirs, last_status));
	if (is_builtin(ast->cmdv[0].argv[0]))
		return (exec_single_builtin(ast, env, last_status));
	return (exec_single_external(ast, env, last_status));
}
