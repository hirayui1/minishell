#include "ft_printf.h"

int ft_hexadec(unsigned long num, int flag)
{
    char *base = flag ? "0123456789ABCDEF" : "0123456789abcdef";
    int sum = 1;
    if (num >= 16)
        sum = ft_hexadec(num / 16, flag) + 1;
    write(1, &base[num % 16], 1);
    return (sum);
}

