#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

int main(void)
{
    printf("=== SIMPLE FT_PRINTF TEST ===\n");
    
    int std_ret, ft_ret;
    
    printf("\n=== Character ===\n");
    std_ret = printf("STD: %c\n", 'A');
    ft_ret = ft_printf("FT:  %c\n", 'A');
    printf("Returns: STD=%d, FT=%d %s\n", std_ret, ft_ret, (std_ret == ft_ret) ? "✓" : "✗");
    
    printf("\n=== String ===\n");
    std_ret = printf("STD: %s\n", "Hello");
    ft_ret = ft_printf("FT:  %s\n", "Hello");
    printf("Returns: STD=%d, FT=%d %s\n", std_ret, ft_ret, (std_ret == ft_ret) ? "✓" : "✗");
    
    printf("\n=== Integer ===\n");
    std_ret = printf("STD: %d\n", 42);
    ft_ret = ft_printf("FT:  %d\n", 42);
    printf("Returns: STD=%d, FT=%d %s\n", std_ret, ft_ret, (std_ret == ft_ret) ? "✓" : "✗");
    
    printf("\n=== Hex ===\n");
    std_ret = printf("STD: %x\n", 255);
    ft_ret = ft_printf("FT:  %x\n", 255);
    printf("Returns: STD=%d, FT=%d %s\n", std_ret, ft_ret, (std_ret == ft_ret) ? "✓" : "✗");
    
    printf("\n=== Multiple Args ===\n");
    std_ret = printf("STD: %d %s\n", 42, "test");
    ft_ret = ft_printf("FT:  %d %s\n", 42, "test");
    printf("Returns: STD=%d, FT=%d %s\n", std_ret, ft_ret, (std_ret == ft_ret) ? "✓" : "✗");
    
    return 0;
}
