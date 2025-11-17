/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:14:13 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/17 13:58:50 by gwindey          ###   ########.fr       */
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

int	builtin_exit(char **argv, int last_status, t_env_entry *env)
{
	long	exit_code;

    // 1. Check voor 'too many arguments'. (Test 51)
	if (argv[1] && argv[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 35);
		return (1);
	}

    // 2. Afhandeling van NIET-NUMERIEK argument (Test 50)
	if (argv[1] && !is_numeric(argv[1]))
	{
		// FIX: Geen "exit\n" en aangepaste prefix
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);

		env_free_all(env);
		exit(2);
	}

    // 3. Afhandeling van GEEN argument
	if (!argv[1])
	{
        // Alleen hier is de write("exit\n") nodig.
        write(STDERR_FILENO, "exit\n", 5);
		env_free_all(env);
		exit(last_status);
	}

    // 4. Afhandeling van GELDIG NUMERIEK argument (Tests 42-49)
    // write("exit\n") is verwijderd.

	exit_code = ft_atol(argv[1]);
	exit_code = (unsigned char)exit_code;
	env_free_all(env);
	exit(exit_code);
}
