/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:43:09 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/02 00:43:09 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_free_cmds(t_commando *cmd)
{
	t_commando	*next;

	while (cmd)
	{
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}
