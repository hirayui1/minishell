#include "ft_printf.h"

int	ft_int_putstr_fd(char *s, int fd)
{
	int	len;

	if (!s)
		return (write(fd, "(null)", 6));
	len = 0;
	if (s)
	{
		len = ft_strlen(s);
		write(fd, s, len);
	}
	return (len);
}
