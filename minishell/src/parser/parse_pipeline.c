/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:24:07 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/19 16:44:27 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tel hoeveel t_commando nodes er in de pipeline zitten
static int	count_commando_nodes(t_commando *cur)
{
	int	count;

	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

// hulp: vul out->cmdv vanuit de gelinkte lisjt
static int	fill_cmdv_from_list(t_commando *cmd_list, t_ast *out, int n)
{
	int			i;
	t_commando	*cur;

	i = 0;
	cur = cmd_list;
	while (i < n)
	{
		out->cmdv[i].argv = cur->argv;
		out->cmdv[i].redirs = cur->redirs;
		cur->argv = NULL;
		cur->redirs = NULL;
		cur = cur->next;
		i++;
	}
	return (1);
}

// zet de t_commando-lijst om naar een t_ast (cmdv-array met argv + redirs)
int	parse_pipeline(t_commando *cmd_list, t_ast *out)
{
	int	n;

	if (!out)
		return (0);
	out->ncmd = 0;
	out->cmdv = NULL;
	n = count_commando_nodes(cmd_list);
	if (n <= 0)
		return (1);
	out->cmdv = (t_command_data *)malloc(sizeof(t_command_data) * n);
	if (!out->cmdv)
		return (0);
	out->ncmd = n;
	return (fill_cmdv_from_list(cmd_list, out, n));
}
