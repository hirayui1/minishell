#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdarg.h>
// run command - cc main.c -L. -lftprintf -o test_printf

int main(void)
{
    int ret_std, ret_ft;

    // 1. Simple string and integer
    ret_std = printf("printf: Hello %s %d!\n", "world", 42);
    ret_ft  = ft_printf("ft_printf: Hello %s %d!\n", "world", 42);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 2. Character
    ret_std = printf("printf: Char = %c\n", 'A');
    ret_ft  = ft_printf("ft_printf: Char = %c\n", 'A');
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 3. Pointer
    void *ptr = &ret_std;
    ret_std = printf("printf: Pointer = %p\n", ptr);
    ret_ft  = ft_printf("ft_printf: Pointer = %p\n", ptr);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 4. Signed integers
    ret_std = printf("printf: int = %d, %i\n", INT_MAX, INT_MIN);
    ret_ft  = ft_printf("ft_printf: int = %d, %i\n", INT_MAX, INT_MIN);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 5. Unsigned integers
    ret_std = printf("printf: unsigned = %u\n", UINT_MAX);
    ret_ft  = ft_printf("ft_printf: unsigned = %u\n", UINT_MAX);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 6. Hexadecimal
    ret_std = printf("printf: hex = %x %X\n", 255, 255);
    ret_ft  = ft_printf("ft_printf: hex = %x %X\n", 255, 255);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 7. Percent literal
    ret_std = printf("printf: 100%% sure\n");
    ret_ft  = ft_printf("ft_printf: 100%% sure\n");
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    // 8. NULL string
    char *null_str = NULL;
    ret_std = printf("printf: null = %s\n", null_str);
    ret_ft  = ft_printf("ft_printf: null = %s\n", null_str);
    printf("Return values: printf=%d, ft_printf=%d\n\n", ret_std, ret_ft);

    return 0;
}
