/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:52:27 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/28 16:52:44 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern void	setup_prompt_signal_handlers(void);

// Checkt of de enige command een geldige builtin is
int	is_single_builtin(t_ast *ast)
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
void	restore_fd(int saved_fd, int target_fd)
{
	if (saved_fd == -1)
		return ;
	dup2(saved_fd, target_fd);
	close(saved_fd);
}

// Wacht op het kindproces, behandelt de status en herstelt de signalen
int	wait_and_handle_external(pid_t pid, int *last_status)
{
	int	status;

	waitpid(pid, &status, 0);
	handle_child_status(status, last_status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	setup_prompt_signal_handlers();
	return (0);
}
