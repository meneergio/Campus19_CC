/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:04:15 by gwindey           #+#    #+#             */
/*   Updated: 2025/09/09 15:37:16 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_duplicate(t_node *stack, int value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	process_args(t_node **stack, char **args)
{
	long	val;
	int		i;
	t_node	*new;

	i = 0;
	while (args[i])
	{
		if (!is_number(args[i]))
			return (0);
		val = ft_atol(args[i]);
		if (val < INT_MIN || val > INT_MAX || is_duplicate(*stack, val))
			return (0);
		new = new_node(val);
		if (!new)
			return (0);
		stack_add_back(stack, new);
		i++;
	}
	return (1);
}

void	parse_input(t_node **stack, int argc, char **argv)
{
	char	**args;

	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args)
			error_exit(stack);
		if (!process_args(stack, args))
		{
			free_split(args);
			error_exit(stack);
		}
		free_split(args);
	}
	else
	{
		if (!process_args(stack, argv + 1))
			error_exit(stack);
	}
}
