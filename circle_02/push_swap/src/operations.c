/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:47:32 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 17:42:56 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_silent(t_node **stack)
{
	t_node	*first;
	t_node	*second;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_node **stack_a)
{
	swap_silent(stack_a);
	write(1, "sa\n", 3);
}

void	sb(t_node **stack_b)
{
	swap_silent(stack_b);
	write(1, "sb\n", 3);
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	swap_silent(stack_a);
	swap_silent(stack_b);
	write(1, "ss\n", 3);
}
/*
Swap:

sa : Wissel de eerste 2 elementen van stack A.
sb : Wissel de eerste 2 elementen van stack B.
ss : Voer tegelijk sa en sb uit.
*/

/*
Push:

pa : Neem het bovenste element van stack B en zet het bovenaan stack A.
pb : Neem het bovenste element van stack A en zet het bovenaan stack B.
*/

/*
Rotate:

ra : Verplaats het eerste element van stack A naar het einde.
rb : Verplaats het eerste element van stack B naar het einde.
rr : Voer tegelijk ra en rb uit.
*/

/*
Reverse rotate:

rra : Verplaats het laatste element van stack A naar voren.
rrb : Verplaats het laatste element van stack B naar voren.
rrr : Voer tegelijk rra en rrb uit.
*/
