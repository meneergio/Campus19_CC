/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwindey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:03:08 by gwindey           #+#    #+#             */
/*   Updated: 2025/05/29 15:16:52 by gwindey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdint.h>
#include <unistd.h>

static int	print_ptr_hex(uintptr_t ptr)
{
	int	len;

	len = 0;
	if (ptr >= 16)
		len += print_ptr_hex(ptr / 16);
	ft_putchar("0123456789abcdef"[ptr % 16]);
	len++;
	return (len);
}

int	ft_putptr(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		len += write(1, "(nil)", 5);
		return (len);
	}
	len += write(1, "0x", 2);
	len += print_ptr_hex((uintptr_t)ptr);
	return (len);
}
/*
#include "ft_printf.h"

int main(void)
{
    void *ptr = (void *)0x7fff1f6e4a00;
    ft_putptr(ptr);  // Should print: 7fff1f6e4a00
    return 0;
}
*/
