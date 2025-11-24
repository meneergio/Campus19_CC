/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:47:40 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/21 15:47:59 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// sluit alle heredoc fd's die al geopend waren
void	cleanup_opened_heredocs(t_ast *ast, int up_to_cmd)
{
	int		i;
	t_redir	*r;

	i = 0;
	while (i < up_to_cmd)
	{
		r = ast->cmdv[i].redirs;
		while (r)
		{
			if (r->type == R_HEREDOC && r->hdoc_fd >= 0)
			{
				close(r->hdoc_fd);
				r->hdoc_fd = -1;
			}
			r = r->next;
		}
		i++;
	}
}

// loop redirs in 1 command en verwerk heredocs
int	prepare_heredocs_one_cmd(t_redir *r, t_env_entry *env)
{
	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			if (!handle_one_heredoc(r, env))
				return (0);
		}
		r = r->next;
	}
	return (1);
}
