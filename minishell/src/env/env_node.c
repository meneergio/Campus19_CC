/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzotti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:37:46 by dzotti            #+#    #+#             */
/*   Updated: 2025/11/18 15:40:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// Als s NULL is, retourneer NULL.
static char	*dup_str(const char *s)
{
	size_t	len;
	char	*out;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s, len + 1);
	return (out);
}

// env_node (key/value als eigen kopieen)
t_env_entry	*env_new_node(const char *key, const char *value)
{
	t_env_entry	*node;

	if (!key || *key == '\0')
		return (NULL);
	node = (t_env_entry *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->key = dup_str(key);
	if (!node->key)
		return (free(node), NULL);
	node->value = dup_str(value);
	if (value != NULL && node->value == NULL)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	env_free_one(t_env_entry *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}
