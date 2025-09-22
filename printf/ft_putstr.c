/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:03:57 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/25 17:20:13 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[len])
	{
		ft_putchar(str[len]);
		len++;
	}
	return (len);
}
/*
#include "ft_printf.h"

int main(void)
{
    ft_putstr("Hello, 42!\n");  // Should print: Hello, 42!
    return 0;
}
*/
