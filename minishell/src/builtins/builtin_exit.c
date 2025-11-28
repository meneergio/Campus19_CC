/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:01:58 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/28 13:57:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

static void	exit_numeric_error(const char *arg, t_env_entry *env)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	env_free_all(env);
	exit(2);
}

// simpel exit zonder argument: exit last_status
static void	simple_exit(int last_status, t_env_entry *env)
{
	env_free_all(env);
	exit(last_status);
}

// builtin exit
int	builtin_exit(char **argv, int last_status, t_env_entry *env)
{
	long	exit_code;

	write(STDOUT_FILENO, "exit\n", 5); 
	if (argv[1] && argv[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 35);
		return (1);
	}
	if (argv[1] && !is_numeric(argv[1]))
		exit_numeric_error(argv[1], env);
	if (!argv[1])
		simple_exit(last_status, env);
	exit_code = ft_atoi(argv[1]);
	exit_code = (unsigned char)exit_code;
	env_free_all(env);
	exit(exit_code);
	return (0);
}
