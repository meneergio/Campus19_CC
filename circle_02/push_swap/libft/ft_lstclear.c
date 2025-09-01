/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:41:37 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/23 14:27:34 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
// Zolang er nodes in de lijst zijn
// Sla de volgende node op, zodat we daarna naar de volgende kunnen gaan
// Verwijder de inhoud van de node en de node zelf
// Verplaats de pointer naar de volgende node
// Na het verwijderen van alle nodes, zet de lijstpointer naar NULL
