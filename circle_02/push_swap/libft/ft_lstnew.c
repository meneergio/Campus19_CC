/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:54:10 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/14 14:58:46 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
	// declares pointer to new node
     // Allocates memory for the new node
     // Sets the content and initialize next to NULL

#include <stdio.h>

int main() {
    // Example content to put into the node (a string in this case)
    char *data = "Hello, world!";
    
    // Create the new node
    t_list *node = ft_lstnew((void *)data);
    
    if (node) {
        // Print content of the new node
        printf("Node content: %s\n", (char *)node->content);
        printf("Node next: %p\n", (void *)node->next);
    } else {
        printf("Failed to create node\n");
    }

    // Free the node (since it is dynamically allocated)
    free(node);
    
    return 0;
}
*/
