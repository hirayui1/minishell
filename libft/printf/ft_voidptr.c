#include "ft_printf.h"

static size_t	p_digits(unsigned long long n)
{
	size_t digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		digits++;
		n /= 16;
	}
	return (digits);
}

static void	print_addr(unsigned long long addr)
{
	static char digits[] = "0123456789abcdef";

	if (addr >= 16)
		print_addr(addr / 16);
	write(1, &digits[addr % 16], 1);
}

int	ft_voidptr(void *addr)
{
	if (!addr)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	print_addr((unsigned long long)addr);
	return (p_digits((unsigned long long)addr) + 2);
}
