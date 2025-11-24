/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:56:53 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/17 19:56:53 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dispatcher: kiest single of pipeline afhankelijk van aantal cmd's
int	execute_ast(t_ast *ast, t_env_entry **env, int *last_status)
{
	if (!ast || ast->ncmd == 0)
		return (1);
	if (ast->ncmd == 1)
		return (execute_single(ast, env, last_status));
	return (execute_pipeline(ast, env, last_status));
}
