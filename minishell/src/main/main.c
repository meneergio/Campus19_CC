/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:46:47 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/28 13:47:17 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	g_exit_status = 0;

// Roept bufferverwerking aan voor inkomende lijnen
static void	handle_input(char *line, t_env_entry **env_head, int *last_status)
{
	if (!line)
		return ;
	process_buffer(line, env_head, last_status);
	free(line);
}

static void	ms_setup(t_env_entry **env_head, char **envp)
{
	*env_head = env_load_from_environ(envp);
	env_bump_shlvl(env_head);
	g_exit_status = 0;
}

// Hoofdlus van minishell
int	main(int argc, char **argv, char **envp)
{
	t_env_entry	*env_head;
	char		*line;
	int			last_status;

	(void)argc;
	(void)argv;
	last_status = 0;
	ms_setup(&env_head, envp);
	while (1)
	{
		terminal_hide_control_chars();
		setup_prompt_signal_handlers();
		line = read_prompt_line();
		terminal_restore_control_chars();
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		handle_input(line, &env_head, &last_status);
	}
	rl_clear_history();
	env_free_all(env_head);
	return (last_status);
}
