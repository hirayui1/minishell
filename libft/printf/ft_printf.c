#include "ft_printf.h"

static int	ft_put_and_free(char *s)
{
	int	len;

	if (!s)
		return (ft_int_putstr_fd("(null)", 1));
	len = ft_int_putstr_fd(s, 1);
	free(s);
	return (len);
}

static int	handle_label(char c, va_list args)
{
	if (c == 'c')
		return (ft_write(va_arg(args, int)));
	else if (c == 's')
		return (ft_int_putstr_fd(va_arg(args, char *), 1));
	else if (c == 'p')
		return (ft_voidptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_put_and_free(ft_itoa(va_arg(args, int))));
	else if (c == 'u')
		return (ft_put_and_free(ft_unsigned_itoa(va_arg(args, unsigned int))));
	else if (c == 'x')
		return (ft_hexadec(va_arg(args, unsigned int), 0));
	else if (c == 'X')
		return (ft_hexadec(va_arg(args, unsigned int), 1));
	else if (c == '%')
		return (ft_write('%'));
	return (0);
}

static int handle_string(const char *format, va_list args)
{
    const char *start = format;
    int sum;

    sum = 0;
    while (*format)
    {
        if (*format == '%')
        {
            if (format > start)
                sum += write(1, start, format - start);
            format++;
            if (*format)
                sum += handle_label(*format++, args);
            start = format;
        }
        else
            format++;
    }
    if (format > start)
        sum += write(1, start, format - start);
    return sum;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		bytes_written;

	va_start(args, format);
	bytes_written = handle_string(format, args);
	va_end(args);
	return (bytes_written);
}

