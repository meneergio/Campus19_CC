/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:43:58 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/25 14:53:56 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL)
		return (NULL);
	if (line[0] != '\0')
		add_history(line);
	return (line);
}
