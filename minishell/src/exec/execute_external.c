/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:54:31 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/21 15:22:02 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Print een foutboodschap en exit met een bepaalde code
static void	exit_with_err(const char *arg, const char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd((char *)msg, 2);
	exit(code);
}

// Checkt of pad bestaat, geen directory is en uitvoerbaar is
static void	check_stat_and_type(t_command_data *cmd, struct stat *st)
{
	if (stat(cmd->argv[0], st) == -1)
		exit_with_err(cmd->argv[0],
			": No such file or directory\n", 127);
	if (S_ISDIR(st->st_mode))
		exit_with_err(cmd->argv[0], ": Is a directory\n", 126);
	if (access(cmd->argv[0], X_OK) == -1)
		exit_with_err(cmd->argv[0], ": Permission denied\n", 126);
}

// Voert een commando uit met een direct pad (./a.out, /bin/ls, ...)
static void	exec_direct_path(t_command_data *cmd, t_env_entry **env)
{
	struct stat	st;
	char		*path;
	char		**envp;

	check_stat_and_type(cmd, &st);
	path = ft_strdup(cmd->argv[0]);
	if (!path)
		exit(1);
	envp = build_envp(*env);
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	exit(126);
}

// Zoekt commando in PATH en voert het uit
static void	exec_from_path(t_command_data *cmd, t_env_entry **env)
{
	char	*path;
	char	**envp;

	path = resolve_cmd_path(cmd->argv[0], *env);
	if (!path)
		exit_with_err(cmd->argv[0], ": command not found\n", 127);
	envp = build_envp(*env);
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	exit(127);
}

// Bepaalt of we direct pad of PATH moeten gebruiken en voert uit
void	execute_external_cmd(t_command_data *cmd, t_env_entry **env)
{
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
		exec_direct_path(cmd, env);
	else
		exec_from_path(cmd, env);
}
