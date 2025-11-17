/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:48:28 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/10 21:17:41 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_unset(char **argv, t_env_entry **env)
{
    if (!argv[1])
        return (0);  // No args = no-op

    int i = 1;
    while (argv[i])
    {
        // Remove node from list
        t_env_entry *prev = NULL;
        t_env_entry *curr = *env;

        while (curr)
        {
            if (strcmp(curr->key, argv[i]) == 0)
            {
                // Found it - remove from list
                if (prev)
                    prev->next = curr->next;
                else
                    *env = curr->next;

                free(curr->key);
                free(curr->value);
                free(curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        i++;
    }
    return (0);
}
