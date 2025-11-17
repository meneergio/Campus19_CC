/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:58:38 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/22 09:44:13 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
// ft_lstmap maakt een nieuwe lijst aan waarin elke node het resultaat bevat 
// van functie 'f' toegepast op de content van de originele lijst.
// Als er een malloc faalt, worden alle eerder aangemaakte nodes van 
// de nieuwe lijst verwijderd met 'ft_lstclear'.
// De originele lijst blijft intact; er wordt niets aan veranderd.
// 'f' wordt gebruikt om nieuwe content te genereren.
// 'del' wordt gebruikt om oude content te verwijderen in geval van error,
// dit voorkomt een meory leak
