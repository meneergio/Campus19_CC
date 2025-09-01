/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:44:41 by gwindey           #+#    #+#             */
/*   Updated: 2025/06/24 18:30:28 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

// Stack operations
t_node	*new_node(int value);
void	stack_add_front(t_node **stack, t_node *new);
void	stack_add_back(t_node **stack, t_node *new);
int		stack_size(t_node *stack);
int		stack_is_sorted(t_node *stack);
void	free_stack(t_node **stack);

// Parsing and error handling
void	parse_input(t_node **stack, int argc, char **argv);
void	error_exit(t_node **stack);

// Push swap operations
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);
void	ss(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);
void	pa(t_node **stack_a, t_node **stack_b);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);
void	rra(t_node **stack_a);
void	rrb(t_node **stack_b);
void	rrr(t_node **stack_a, t_node **stack_b);

// Indexing
void	index_stack(t_node *stack);

// Sorting algorithms
void	sort_three(t_node **stack_a);
void	sort_five(t_node **stack_a, t_node **stack_b);
void	chunk_sort(t_node **stack_a, t_node **stack_b);
void	radix_sort(t_node **stack_a, t_node **stack_b);
void	hybrid_sort(t_node **a, t_node **b, int size);
int		calculate_move_cost(t_node *stack, int target_index);
int		find_most_efficient_element(t_node *stack,
			int min_range, int max_range);

// Helper functions
int		find_min_position(t_node *stack);
int		find_max_index(t_node *stack);
int		find_position_by_index(t_node *stack, int target_index);
int		find_max_position(t_node *stack);

// Optimization_helpers
int		is_in_range(int index, int min, int max);
int		find_closest_in_range(t_node *stack, int min, int max);
void	rotate_to_position(t_node **stack, int target_pos, char stack_name);
void	optimized_chunk_sort(t_node **stack_a, t_node **stack_b);
void	presort_small_groups(t_node **stack_a);
int		get_chunk_size(int total_size);
void	push_back_optimized(t_node **stack_a, t_node **stack_b);
void	optimized_large_sort(t_node **a, t_node **b, int size);
int		count_elements_in_chunk(t_node *a, int min_range, int max_range);

#endif
