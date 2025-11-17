/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:51:15 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/13 13:38:23 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl C
static void	sigint_in_prompt(int sig)
{
	(void)sig;
	shell_set_signal(SIGINT);

	// Nieuw: altijd nieuwe regel en prompt op aparte regel
	write(STDOUT_FILENO, "\n", 1);

	// Herstel readline buffer
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_prompt_signal_handlers(void)
{
	struct sigaction	sa;

	// SIGINT handler (Ctrl+C)
	sa.sa_handler = sigint_in_prompt;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	// SIGQUIT handler (Ctrl+\) - NEGEER VOLLEDIG
	sa.sa_handler = SIG_IGN;  // ← Dit is de fix!
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
