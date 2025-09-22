/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:15:16 by gwindey           #+#    #+#             */
/*   Updated: 2025/04/25 15:22:58 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_conversion(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), c));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}
/*
#include <stdarg.h>

int	test_handle(char specifier, ...)
{
	va_list	args;
	int		len;

	va_start(args, specifier);
	len = handle_conversion(specifier, args);
	va_end(args);
	return (len);
}

int	main(void)
{
	test_handle('c', 'A');                 // should print: A
	test_handle('s', "Hello");             // should print: Hello
	test_handle('d', 42);                  // should print: 42
	test_handle('i', -42);                 // should print: -42
	test_handle('u', 4294967295U);         // should print: 4294967295
	test_handle('x', 255);                 // should print: ff
	test_handle('X', 255);                 // should print: FF
	test_handle('p', (void *)0x1234);      // should print: 0x1234
	test_handle('%');                      // should print: %

	return (0);
}
*/
