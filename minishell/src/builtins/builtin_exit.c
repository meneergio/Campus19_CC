/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:01:58 by dzotti            #+#    #+#             */
/*   Updated: 2025/12/01 17:20:34 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** SPECIAL EXIT RETURN VALUES:
** We use return values >= 512 to signal that the shell should exit
** 512 + exit_code = signal to exit with that code
** This allows proper cleanup before exit()
*/

#define EXIT_SIGNAL_BASE 512

static int	ft_isdigit_char(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** builtin_exit: Handle the exit builtin
** Returns:
** - 1 if too many arguments (don't exit, just error)
** - EXIT_SIGNAL_BASE + exit_code to signal main loop to cleanup and exit
*/
int	builtin_exit(char **argv, int last_status, t_env_entry *env)
{
	long	exit_code;

	(void)env;
	write(STDOUT_FILENO, "exit\n", 5);
	if (argv[1] && argv[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	if (argv[1] && !is_numeric(argv[1]))
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		return (EXIT_SIGNAL_BASE + 2);
	}
	if (!argv[1])
		exit_code = last_status;
	else
		exit_code = ft_atoi(argv[1]);
	exit_code = (unsigned char)exit_code;
	return (EXIT_SIGNAL_BASE + (int)exit_code);
}

