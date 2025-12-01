/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_ast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:52:45 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/10 19:11:20 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free gelinkte lijst van redir (arg + eventueel hdoc-fd)
static void	free_redir_list(t_redir *r)
{
	t_redir	*next;

	while (r)
	{
		next = r->next;
		if (r->arg)
			free(r->arg);
		if (r->type == R_HEREDOC && r->hdoc_fd >= 0)
			close(r->hdoc_fd);
		free(r);
		r = next;
	}
}

// free argv-array: alle strings + de array zelf
static void	free_argv_array(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

// free volledige AST: alle commands, argv en redirs
void	free_ast(t_ast *ast)
{
	int	i;

	if (!ast || !ast->cmdv)
		return ;
	i = 0;
	while (i < ast->ncmd)
	{
		free_argv_array(ast->cmdv[i].argv);
		free_redir_list(ast->cmdv[i].redirs);
		i++;
	}
	free(ast->cmdv);
	ast->cmdv = NULL;
	ast->ncmd = 0;
}
