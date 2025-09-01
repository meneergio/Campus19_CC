/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:26:12 by gwindey           #+#    #+#             */
/*   Updated: 2025/08/12 10:28:19 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_ack_received = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

int	validate_pid(pid_t pid)
{
	if (pid <= 0 || pid > 4194304)
	{
		ft_printf("Error: Invalid PID range\n");
		return (0);
	}
	if (kill(pid, 0) == -1)
	{
		ft_printf("Error: Process %d does not exist or no permission\n", pid);
		return (0);
	}
	return (1);
}

void	send_bit_with_retry(pid_t server_pid, int bit_value)
{
	int	timeout;
	int	retry_count;

	retry_count = 0;
	while (retry_count < 3)
	{
		if (bit_value)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		if (retry_count == 0)
			timeout = 50000;
		else
			timeout = 100000;
		while (!g_ack_received && timeout-- > 0)
			usleep(1);
		if (g_ack_received)
			return ;
		retry_count++;
		usleep(1000);
	}
	ft_printf("Error: Server not responding\n");
	exit(1);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_ack_received = 0;
		send_bit_with_retry(server_pid, c & (1 << bit));
		bit--;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;
	int					i;

	if (argc != 3)
		return (ft_printf("Usage: %s [server_PID] [message]\n", argv[0]), 1);
	server_pid = ft_atoi(argv[1]);
	if (!validate_pid(server_pid))
		return (1);
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (ft_printf("Error: Failed to set signal handler\n"), 1);
	i = -1;
	while (argv[2][++i])
		send_char(server_pid, argv[2][i]);
	send_char(server_pid, '\0');
	return (0);
}
