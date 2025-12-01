/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:27:08 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/12 10:18:45 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server_data	g_server;

void	reset_server_state(void)
{
	g_server.received_char = 0;
	g_server.bit_count = 0;
}

void	process_bit(int sig)
{
	g_server.received_char <<= 1;
	if (sig == SIGUSR2)
		g_server.received_char |= 1;
	g_server.bit_count++;
}

void	process_complete_char(void)
{
	if (g_server.received_char == '\0')
	{
		write(STDOUT_FILENO, "\n", 1);
		reset_server_state();
		return ;
	}
	write(STDOUT_FILENO, &g_server.received_char, 1);
	reset_server_state();
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_server.client_pid != 0 && g_server.client_pid != info->si_pid)
		reset_server_state();
	g_server.client_pid = info->si_pid;
	process_bit(sig);
	if (kill(g_server.client_pid, SIGUSR1) == -1)
		reset_server_state();
	if (g_server.bit_count == 8)
		process_complete_char();
}

int	main(void)
{
	struct sigaction	sa;

	reset_server_state();
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: sigaction failed\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
