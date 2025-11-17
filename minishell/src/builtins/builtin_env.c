/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:12:08 by gwindey           #+#    #+#             */
/*   Updated: 2025/11/12 14:05:10 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	builtin_env(t_env_entry *env)
{
	t_env_entry	*p;

	p = env;
	while (p)
	{
		if (ft_strncmp(p->key, "?", 2) != 0)
			printf("%s=%s\n", p->key, p->value);
		p = p->next;
	}
	return (0);
}
