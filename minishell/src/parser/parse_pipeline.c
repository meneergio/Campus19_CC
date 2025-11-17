/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:24:07 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/10 20:35:20 by gwindey          ###   ########.fr       */
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

// zet de t_commando-lijst om naar een t_ast (cmdv-array met argv + redirs)
int	parse_pipeline(t_commando *cmd_list, t_ast *out)
{
	int			i;
	int			n;
	t_commando	*cur;

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
	i = 0;
	cur = cmd_list;
	while (i < n)
	{
		out->cmdv[i].argv = cur->argv;
		out->cmdv[i].redirs = cur->redirs;
		cur = cur->next;
		i++;
	}
	out->ncmd = n;
	return (1);
}
