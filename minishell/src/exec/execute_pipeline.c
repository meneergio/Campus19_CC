/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:05:19 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/28 16:18:00 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern void	setup_prompt_signal_handlers(void);

// Maakt alle pipes voor de pipeline aan
static int	open_pipes(t_pipe_ctx *ctx)
{
	int	i;
	int	count;

	count = ctx->ast->ncmd - 1;
	i = 0;
	while (i < count)
	{
		if (pipe(ctx->pipes[i]) == -1)
		{
			perror("pipe");
			close_all_pipes(i, ctx->pipes);
			return (1);
		}
		i++;
	}
	return (0);
}

// Code die in elk pipeline-child draait (redirs + builtin/exec)
static void	child_process(t_pipe_ctx *ctx, int i)
{
	int	j;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i > 0)
		dup2(ctx->pipes[i - 1][0], STDIN_FILENO);
	if (i < ctx->ast->ncmd - 1)
		dup2(ctx->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < ctx->ast->ncmd - 1)
	{
		close(ctx->pipes[j][0]);
		close(ctx->pipes[j][1]);
		j++;
	}
	if (apply_redirs(ctx->ast->cmdv[i].redirs) != 0)
		exit(1);
	close_all_heredoc_fds(ctx->ast);
	if (ctx->ast->cmdv[i].argv && is_builtin(ctx->ast->cmdv[i].argv[0]))
		exit(run_builtin(ctx->ast->cmdv[i].argv, ctx->env, 0));
	execute_external_cmd(&ctx->ast->cmdv[i], ctx->env);
	exit(127);
}

// Forkt alle children
static int	spawn_children(t_pipe_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->ast->ncmd)
	{
		ctx->pids[i] = fork();
		if (ctx->pids[i] == -1)
		{
			perror("fork");
			close_all_pipes(ctx->ast->ncmd - 1, ctx->pipes);
			wait_spawned_children(i, ctx->pids);
			return (1);
		}
		if (ctx->pids[i] == 0)
			child_process(ctx, i);
		i++;
	}
	return (0);
}

// Wacht op alle children en herstelt de terminal naar de shell
static void	wait_and_cleanup(t_pipe_ctx *ctx)
{
	int		i;
	int		status;
	int		last_was_sigint;

	last_was_sigint = 0;
	close_all_pipes(ctx->ast->ncmd - 1, ctx->pipes);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i < ctx->ast->ncmd)
	{
		waitpid(ctx->pids[i], &status, 0);
		if (i == ctx->ast->ncmd - 1)
		{
			handle_child_status(status, ctx->last_status);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				last_was_sigint = 1;
		}
		i++;
	}
	if (last_was_sigint)
		write(STDOUT_FILENO, "\n", 1);
	fflush(stdout);
	setup_prompt_signal_handlers();
}

// Hoofdfunctie: voert een pipeline (ncmd > 1) uit
int	execute_pipeline(t_ast *ast, t_env_entry **env, int *last_status)
{
	t_pipe_ctx	ctx;

	ctx.ast = ast;
	ctx.env = env;
	ctx.last_status = last_status;
	ctx.pipes = malloc(sizeof(int [2]) * (ast->ncmd - 1));
	ctx.pids = malloc(sizeof(pid_t) * ast->ncmd);
	if (!ctx.pipes || !ctx.pids)
	{
		ft_putstr_fd("minishell: allocation error\n", 2);
		return (free_pipe_data(ctx.pipes, ctx.pids));
	}
	if (open_pipes(&ctx) != 0)
		return (free_pipe_data(ctx.pipes, ctx.pids));
	terminal_restore_control_chars();
	if (spawn_children(&ctx) != 0)
		return (free_pipe_data(ctx.pipes, ctx.pids));
	wait_and_cleanup(&ctx);
	free(ctx.pipes);
	free(ctx.pids);
	return (0);
}
