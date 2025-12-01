/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:47:57 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/17 20:47:57 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Splits buffer op '\n' en verwerkt elke subregel
void	process_buffer(char *buf, t_env_entry **env_head, int *last_status)
{
	char	*p;
	char	*start;

	if (!buf || !*buf)
		return ;
	start = buf;
	p = buf;
	while (*p)
	{
		if (*p == '\n')
		{
			*p = '\0';
			if (*start)
				process_one_line(start, env_head, last_status);
			start = p + 1;
		}
		p++;
	}
	if (*start)
		process_one_line(start, env_head, last_status);
}
