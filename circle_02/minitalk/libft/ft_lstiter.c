/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:50:41 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/22 14:57:26 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
// past de functie 'f' toe op de content van elke node in de gelinkte lijst.
// Het doorloopt de hele lijst node per node met een while-lus.
// Bij elke stap wordt de functie 'f' uitgevoerd met lst->content als argument.
// Daarna wordt lst verplaatst naar de volgende node (lst = lst->next).
// De functie verandert de lijststructuur zelf niet, 
// alleen de inhoud van nodes kan aangepast worden.
