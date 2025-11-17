/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:10:17 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/09 23:10:17 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	debug_print_argv(char **argv)
{
	int	i;

	if (!argv || !argv[0])
	{
		printf("  argv: (none)\n");
		return ;
	}
	printf("  argv:");
	i = 0;
	while (argv[i])
	{
		printf(" [%s]", argv[i]);
		i++;
	}
	printf("\n");
}

static const char	*redir_name(t_rtype type)
{
	if (type == R_IN)
		return ("R_IN");
	if (type == R_OUT)
		return ("R_OUT");
	if (type == R_APPEND)
		return ("R_APPEND");
	if (type == R_HEREDOC)
		return ("R_HEREDOC");
	return ("?(bad)");
}

static void	debug_print_redirs(t_redir *r)
{
	const char	*arg;

	if (!r)
	{
		printf("  redirs: (none)\n");
		return ;
	}
	while (r)
	{
		arg = r->arg;
		if (!arg)
			arg = "(null)";
		printf("  redir %s -> %s\n", redir_name(r->type), arg);
		r = r->next;
	}
}

void	debug_print_cmd_built(t_commando *cmd)
{
	t_commando	*c;

	c = cmd;
	while (c)
	{
		printf("== command ==\n");
		debug_print_argv(c->argv);
		debug_print_redirs(c->redirs);
		c = c->next;
	}
}
