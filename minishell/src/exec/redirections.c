/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:31:08 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/27 16:07:08 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Print een redirect-foutboodschap en geef -1 terug
static int	redir_error(char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

// Handelt R_IN, R_OUT en R_APPEND af voor één redirect-node
static int	handle_file_redir(t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == R_IN)
		fd = open(r->arg, O_RDONLY);
	else if (r->type == R_OUT)
		fd = open(r->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == R_APPEND)
		fd = open(r->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		if (r->type == R_IN)
			return (redir_error(r->arg, "No such file or directory"));
		return (redir_error(r->arg, "Permission denied"));
	}
	if (r->type == R_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

// Handelt een heredoc-redirect af (fd naar stdin dupen)
static int	handle_heredoc_redir(t_redir *r)
{
	if (r->type == R_HEREDOC && r->hdoc_fd >= 0)
	{
		dup2(r->hdoc_fd, STDIN_FILENO);
		close(r->hdoc_fd);
	}
	return (0);
}

// Loopt over alle redirects en past ze in volgorde toe
int	apply_redirs(t_redir *redirs)
{
	t_redir	*r;
	int		res;

	r = redirs;
	while (r)
	{
		res = 0;
		if (r->type == R_IN || r->type == R_OUT || r->type == R_APPEND)
			res = handle_file_redir(r);
		else if (r->type == R_HEREDOC)
			res = handle_heredoc_redir(r);
		if (res != 0)
			return (-1);
		r = r->next;
	}
	return (0);
}

// Handle lege redirect zonder commando (bijv. "> file")
int	handle_empty_redirect(t_redir *redirs, int *last_status)
{
	int	orig_in;
	int	orig_out;

	if (!redirs)
		return (0);
	orig_in = dup(STDIN_FILENO);
	orig_out = dup(STDOUT_FILENO);
	if (apply_redirs(redirs) != 0)
		*last_status = 1;
	else
		*last_status = 0;
	if (orig_in != -1)
	{
		dup2(orig_in, STDIN_FILENO);
		close(orig_in);
	}
	if (orig_out != -1)
	{
		dup2(orig_out, STDOUT_FILENO);
		close(orig_out);
	}
	return (0);
}
