/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:37:37 by dzotti            #+#    #+#             */
/*   Updated: 2025/10/17 18:37:37 by dzotti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// voeg node achteraan toe
void	env_append(t_env_entry **lst, t_env_entry *node)
{
	t_env_entry	*p;

	if (!lst || !node)
		return ;
	node->next = NULL;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = node;
}

// free hele lijst
void	env_free_all(t_env_entry *head)
{
	t_env_entry	*next;

	while (head)
	{
		next = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = next;
	}
}

// zoek exacte key, return value of NULL
const char	*env_find_value(t_env_entry *head, const char *key)
{
	t_env_entry	*p;

	if (!head || !key || *key == '\0')
		return (NULL);
	p = head;
	while (p)
	{
		if (ft_strncmp(p->key, key, ft_strlen(p->key) + 1) == 0)
			return (p->value);
		p = p->next;
	}
	return (NULL);
}

// zoek exacte key maar geeft NODE terug ipv alleen value
t_env_entry	*env_find_node(t_env_entry *head, const char *key)
{
	t_env_entry	*p;

	if (!head || !key || *key == '\0')
		return (NULL);
	p = head;
	while (p)
	{
		if (ft_strncmp(p->key, key, ft_strlen(p->key) + 1) == 0)
			return (p);
		p = p->next;
	}
	return (NULL);
}
