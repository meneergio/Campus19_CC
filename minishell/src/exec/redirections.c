/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:48:21 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/17 14:03:53 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// FIX: Veilige, custom foutmelding die direct de verwachte fout schrijft
static int	redir_error(char *arg)
{
    // FIX: Gebruik ft_putstr_fd om de volledige Bash-stijl foutmelding te garanderen
    // De garbled output vereist dat we de foutboodschap op een stabiele manier schrijven.
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int apply_redirs(t_redir *redirs)
{
    int fd;
    t_redir *r = redirs;

    while (r)
    {
        if (r->type == R_IN)
        {
            fd = open(r->arg, O_RDONLY);
            // ⚠️ FIX: Vervang 'perror(r->arg); return (-1);' door de custom functie
            if (fd < 0) {
                return (redir_error(r->arg));
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        else if (r->type == R_OUT)
        {
            fd = open(r->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
             // ⚠️ FIX: Vervang 'perror(r->arg); return (-1);'
            if (fd < 0) {
                return (redir_error(r->arg));
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == R_APPEND)
        {
            fd = open(r->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
             // ⚠️ FIX: Vervang 'perror(r->arg); return (-1);'
            if (fd < 0) {
                return (redir_error(r->arg));
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (r->type == R_HEREDOC && r->hdoc_fd >= 0)
        {
            dup2(r->hdoc_fd, STDIN_FILENO);
            close(r->hdoc_fd);
        }

        r = r->next;
    }
    return (0);
}
