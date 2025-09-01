/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:56:34 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/15 16:47:22 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*ft_lstdelone verwijdert één knooppunt uit een gelinkte lijst door eerst 
de inhoud te verwijderen met een opgegeven functie en daarna het knooppunt 
zelf vrij te geven.*/
