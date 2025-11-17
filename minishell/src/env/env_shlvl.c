/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:35:28 by dzotti            #+#    #+#             */
/*   Updated: 2025/10/31 15:35:28 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// lees string SHLVL -> maak veilig getal
static int	shlvl_parse(const char *s)
{
	int	n;

	if (!s || *s == '\0')
		return (0);
	n = ft_atoi(s);
	if (n < 0)
		return (0);
	return (n);
}

// zorg dat SHLVL in de lijst staat en +1 is
void	env_bump_shlvl(t_env_entry **head)
{
	t_env_entry	*node;
	char		*str;
	int			lvl;

	if (head == NULL || *head == NULL)
		return ;
	lvl = shlvl_parse(env_find_value(*head, "SHLVL"));
	lvl++;
	node = env_find_node(*head, "SHLVL");
	str = ft_itoa(lvl);
	if (str == NULL)
		return ;
	if (node)
	{
		free(node->value);
		node->value = str;
	}
	else
	{
		env_append(head, env_new_node("SHLVL", str));
		free(str);
	}
}
