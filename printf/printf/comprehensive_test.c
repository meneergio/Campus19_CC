#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

void test_conversion(char *desc, char *format, ...)
{
    va_list args1, args2;
    int std_ret, ft_ret;
    
    printf("\n=== %s ===\n", desc);
    
    va_start(args1, format);
    va_start(args2, format);
    
    printf("STD: ");
    std_ret = vprintf(format, args1);
    printf("\nFT:  ");
    ft_ret = ft_printf(format, args2);
    
    printf("\nReturn values: STD=%d, FT=%d %s\n", 
           std_ret, ft_ret, (std_ret == ft_ret) ? "✓" : "✗ FAIL");
    
    va_end(args1);
    va_end(args2);
}

int main(void)
{
    printf("=== COMPREHENSIVE FT_PRINTF TEST ===\n");
    
    // Basic tests
    test_conversion("Character", "%c", 'A');
    test_conversion("String", "%s", "Hello World");
    test_conversion("Null String", "%s", (char *)NULL);
    test_conversion("Empty String", "%s", "");
    test_conversion("Integer", "%d", 42);
    test_conversion("Negative Int", "%d", -42);
    test_conversion("Zero", "%d", 0);
    test_conversion("INT_MAX", "%d", INT_MAX);
    test_conversion("INT_MIN", "%d", INT_MIN);
    test_conversion("Unsigned", "%u", 42U);
    test_conversion("Unsigned Zero", "%u", 0U);
    test_conversion("UINT_MAX", "%u", UINT_MAX);
    test_conversion("Hex Lower", "%x", 255);
    test_conversion("Hex Upper", "%X", 255);
    test_conversion("Hex Zero", "%x", 0);
    
    void *ptr = (void *)0x12345678;
    test_conversion("Pointer", "%p", ptr);
    test_conversion("NULL Pointer", "%p", (void *)NULL);
    test_conversion("Percent", "%%");
    
    // Mixed tests
    test_conversion("Mixed", "Int: %d, Str: %s, Hex: %x", 42, "test", 255);
    test_conversion("Multiple Same", "%d %d %d", 1, 2, 3);
    
    // Edge cases
    test_conversion("No Format", "Just text");
    test_conversion("Empty", "");
    
    printf("\n=== TEST COMPLETE ===\n");
    return 0;
}
