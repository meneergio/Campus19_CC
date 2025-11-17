/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:35:18 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/17 14:04:42 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* Externe setup voor signal handlers in de prompt (readline) */
extern void setup_prompt_signal_handlers(void);

/* Hanteer child-status (exit / signaal) */
static void handle_child_status(int status, int *last_status)
{
    if (WIFEXITED(status))
        *last_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        *last_status = 128 + WTERMSIG(status);


        if (WTERMSIG(status) == SIGQUIT)
            ft_putstr_fd("Quit (core dumped)\n", 2);
    }
}

/* Helper voor atomische error messages (voorkomt interleaving in pipelines) */
static void    print_cmd_error(const char *cmd, const char *msg)
{
    char    buffer[1024];
    int        len;
    int        i;
    const char *prefix = "minishell: ";
    const char *sep = ": ";

    len = 0;
    i = 0;
    while (prefix[i] && len < 1020)
        buffer[len++] = prefix[i++];
    i = 0;
    while (cmd && cmd[i] && len < 1020)
        buffer[len++] = cmd[i++];
    i = 0;
    while (sep[i] && len < 1020)
        buffer[len++] = sep[i++];
    i = 0;
    while (msg && msg[i] && len < 1020)
        buffer[len++] = msg[i++];
    if (len < 1023)
        buffer[len++] = '\n';
    write(2, buffer, len);
}

/* Execve helper voor externe commands */
void execute_external_cmd(t_command_data *cmd, t_env_entry **env)
{
	char			*path;
	char			**envp;
	struct stat		st;

	if (!cmd->argv || !cmd->argv[0])
		exit(0);

	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
	{
		if (stat(cmd->argv[0], &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				print_cmd_error(cmd->argv[0], "Is a directory");
				exit(126);
			}
			if (access(cmd->argv[0], X_OK) == -1)
			{
				print_cmd_error(cmd->argv[0], "Permission denied");
				exit(126);
			}
			path = ft_strdup(cmd->argv[0]);
			envp = build_envp(*env);
			execve(path, cmd->argv, envp);
			perror(cmd->argv[0]);
			exit(126);
		}
		else
		{
			print_cmd_error(cmd->argv[0], "No such file or directory");
			exit(127);
		}
	}

	path = resolve_cmd_path(cmd->argv[0], *env);
	if (!path)
	{
		print_cmd_error(cmd->argv[0], "command not found");
		exit(127);
	}
	envp = build_envp(*env);
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	exit(127);
}

/*
 * execute_ast:
 */
int execute_ast(t_ast *ast, t_env_entry **env, int *last_status)
{
	int				(*pipes)[2];
	pid_t			*pids;
	int				i, j, status;
	pid_t			first_pgid = 0;
	pid_t			shell_pgid;

	if (!ast || ast->ncmd == 0)
		return (1);

	/* -------------------- SINGLE COMMAND -------------------- */
	if (ast->ncmd == 1)
	{
		if (!ast->cmdv[0].argv || !ast->cmdv[0].argv[0])
			return (0);
		if (ast->cmdv[0].argv && is_builtin(ast->cmdv[0].argv[0]))
		{
			int	orig_stdin = dup(STDIN_FILENO);
			int	orig_stdout = dup(STDOUT_FILENO);

			if (apply_redirs(ast->cmdv[0].redirs) == 0)
				*last_status = run_builtin(ast->cmdv[0].argv, env, *last_status);
			else
				*last_status = 1;

			if (orig_stdin != -1)
			{
				dup2(orig_stdin, STDIN_FILENO);
				close(orig_stdin);
			}
			if (orig_stdout != -1)
			{
				dup2(orig_stdout, STDOUT_FILENO);
				close(orig_stdout);
			}
			return (0);
		}

		/* external in child */
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid_t pid = fork();
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

	/* -------------------- PIPELINE -------------------- */

	/* alloc */
	pipes = malloc(sizeof(int[2]) * (ast->ncmd - 1));
	pids = malloc(sizeof(pid_t) * ast->ncmd);
	if (!pipes || !pids)
	{
		ft_putstr_fd("minishell: allocation error\n", 2);
		free(pipes);
		free(pids);
		return (1);
	}

	/* create pipes */
	for (i = 0; i < ast->ncmd - 1; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			for (j = 0; j < i; j++)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			free(pipes);
			free(pids);
			return (1);
		}
	}

	/* remember shell pgid so we can restore terminal after job */
	shell_pgid = getpgrp();

	/* Fork each command and arrange process groups: */
	for (i = 0; i < ast->ncmd; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			for (j = 0; j < ast->ncmd - 1; j++)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}
			for (j = 0; j < i; j++)
				waitpid(pids[j], NULL, 0);
			free(pipes);
			free(pids);
			return (1);
		}

		if (pids[i] == 0)
		{
			/* CHILD */
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			/* set pgid: children set their pgid appropriately */
			if (i == 0)
			{
				if (setpgid(0, 0) == -1)
					; /* best effort */
			}
			else
			{
				/* join first child's pgid (we expect parent set it, but try best-effort) */
				if (setpgid(0, first_pgid) == -1)
					; /* best effort */
			}

			/* connect pipes */
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < ast->ncmd - 1)
				dup2(pipes[i][1], STDOUT_FILENO);

			/* close all pipe fds in child */
			for (j = 0; j < ast->ncmd - 1; j++)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
			}

            // ⚠️ FIX VOOR DUBBELE REDIRECT FOUTMELDING
			if (apply_redirs(ast->cmdv[i].redirs) != 0)
				exit(1); // Stop direct na redirect fout

			if (ast->cmdv[i].argv && is_builtin(ast->cmdv[i].argv[0]))
				exit(run_builtin(ast->cmdv[i].argv, env, *last_status));
			else
				execute_external_cmd(&ast->cmdv[i], env);
			exit(127);
		}
		else
		{
			/* PARENT: ensure child is in the correct pgid (avoid race) */
			if (i == 0)
			{
				/* make first child leader of its pgid */
				first_pgid = pids[0];
				if (setpgid(pids[0], pids[0]) == -1 && errno != EACCES)
					; /* ignore best-effort errors */
			}
			else
			{
				if (setpgid(pids[i], first_pgid) == -1 && errno != EACCES)
					; /* ignore best-effort errors */
			}
		}
	}

	/* parent closes pipes */
	for (i = 0; i < ast->ncmd - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}

	/* parent: ignore SIGINT/SIGQUIT while we manage job/terminal */
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	/* Temporarily ignore SIGTTOU so tcsetpgrp won't stop the parent */
	void (*old_ttou)(int) = signal(SIGTTOU, SIG_IGN);

	/* Give terminal to the job's process group (so children receive Ctrl-C) */
	if (first_pgid != 0)
	{
		if (tcsetpgrp(STDIN_FILENO, first_pgid) == -1)
		{
			/* not fatal: continue — best-effort to emulate bash-3.2 behavior */
		}
	}

	/* Wait for all children (blocking) — bash-3.2 behaviour expects this */
	for (i = 0; i < ast->ncmd; i++)
	{
		waitpid(pids[i], &status, 0);
		if (i == ast->ncmd - 1)
			handle_child_status(status, last_status);
	}

	// flush stdout zodat alle output van de pipeline zichtbaar wordt
	fflush(stdout);

	/* Restore terminal ownership to shell */
	if (tcsetpgrp(STDIN_FILENO, shell_pgid) == -1)
	{
		/* ignore */
	}

	/* Restore SIGTTOU handler */
	signal(SIGTTOU, old_ttou);

	/* Restore prompt signal handlers (readline) */
	setup_prompt_signal_handlers();

	free(pipes);
	free(pids);
	return (0);
}
