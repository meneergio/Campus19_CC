/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:56:36 by gwindey           #+#    #+#             */
/*   Updated: 2025/05/29 15:26:29 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	process_conversion(char c, va_list args)
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

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	if (!format)
		return (-1);
	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				len += process_conversion(*format, args);
			else
				break ;
		}
		else
			len += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (len);
}
/*
#include <stddef.h>
int main(void)
{
	ft_printf("Test string: %s\n", NULL);
}
*/
/*
#include "ft_printf.h"

int main(void)
{
    ft_printf("Testing ft_printf with some conversions:\n");
    ft_printf("Char: %c\n", 'A');
    ft_printf("String: %s\n", "Hello, 42!");
    ft_printf("Int: %d\n", 123);
    ft_printf("Hex lowercase: %x\n", 255);
    ft_printf("Hex uppercase: %X\n", 255);
    ft_printf("Unsigned: %u\n", 4294967295);
    ft_printf("Pointer: %p\n", (void *)0x7fff1f6e4a00);
    ft_printf("Percent: %%\n");
    return 0;
}
*/
/*expected:
Testing ft_printf with some conversions:
Char: A
String: Hello, 42!
Int: 123
Hex lowercase: ff
Hex uppercase: FF
Unsigned: 4294967295
Pointer: 0x7fff1f6e4a00
Percent: %
*/
/*
#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

int	main(void)
{
	int	ret_std, ret_ft;
	ft_printf(0);
	printf(0);
	// %c tests
	printf("== %%c tests ==\n");
	ret_std = printf("STD: [%c]\n", 'A');
	ret_ft = ft_printf("FT : [%c]\n", 'A');
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%c]\n", '\0');
	ret_ft = ft_printf("FT : [%c]\n", '\0');
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	// %s tests
	printf("== %%s tests ==\n");
	ret_std = printf("STD: [%s]\n", "Hello");
	ret_ft = ft_printf("FT : [%s]\n", "Hello");
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%s]\n", "");
	ret_ft = ft_printf("FT : [%s]\n", "");
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%s]\n", NULL);
	ret_ft = ft_printf("FT : [%s]\n", NULL);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	// %d and %i tests
	printf("== %%d/%%i tests ==\n");
	ret_std = printf("STD: [%d] [%i]\n", 42, -42);
	ret_ft = ft_printf("FT : [%d] [%i]\n", 42, -42);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%d]\n", INT_MAX);
	ret_ft = ft_printf("FT : [%d]\n", INT_MAX);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%d]\n", INT_MIN);
	ret_ft = ft_printf("FT : [%d]\n", INT_MIN);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	// %u tests
	printf("== %%u tests ==\n");
	ret_std = printf("STD: [%u]\n", 0);
	ret_ft = ft_printf("FT : [%u]\n", 0);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%u]\n", UINT_MAX);
	ret_ft = ft_printf("FT : [%u]\n", UINT_MAX);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	// %x / %X tests
	printf("== %%x/%%X tests ==\n");
	ret_std = printf("STD: [%x] [%X]\n", 255, 255);
	ret_ft = ft_printf("FT : [%x] [%X]\n", 255, 255);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%x] [%X]\n", UINT_MAX, UINT_MAX);
	ret_ft = ft_printf("FT : [%x] [%X]\n", UINT_MAX, UINT_MAX);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	// %p tests
	printf("== %%p tests ==\n");
	int a = 42;
	ret_std = printf("STD: [%p]\n", &a);
	ret_ft = ft_printf("FT : [%p]\n", &a);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	ret_std = printf("STD: [%p]\n", NULL);
	ret_ft = ft_printf("FT : [%p]\n", NULL);
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	// %% test
	printf("== %%%% test ==\n");
	ret_std = printf("STD: [%%]\n");
	ret_ft = ft_printf("FT : [%%]\n");
	printf("Return values: STD=%d, FT=%d\n\n", ret_std, ret_ft);

	return (0);
}
*/
