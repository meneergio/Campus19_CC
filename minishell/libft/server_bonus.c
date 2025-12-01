/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:15:32 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/12 10:20:17 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_char = 0;
int		g_bits = 0;
pid_t	g_pid = 0;

void	reset_bonus_state(void)
{
	g_char = 0;
	g_bits = 0;
}

void	process_bit_bonus(int sig)
{
	g_char <<= 1;
	if (sig == SIGUSR2)
		g_char |= 1;
	g_bits++;
	if (kill(g_pid, SIGUSR1) == -1)
		reset_bonus_state();
}

void	process_complete_char_bonus(void)
{
	if (g_char == '\0')
	{
		write(1, "\n", 1);
		if (kill(g_pid, SIGUSR2) == -1)
			reset_bonus_state();
		reset_bonus_state();
		return ;
	}
	write(1, &g_char, 1);
	reset_bonus_state();
}

void	signal_handler_bonus(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_pid != 0 && g_pid != info->si_pid)
		reset_bonus_state();
	g_pid = info->si_pid;
	process_bit_bonus(sig);
	if (g_bits == 8)
		process_complete_char_bonus();
}

int	main(void)
{
	struct sigaction	sa;

	reset_bonus_state();
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = signal_handler_bonus;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || \
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: Failed to set signal handlers\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
