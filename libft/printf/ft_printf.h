#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_printf(const char *, ...);
int	ft_write(char c);
int	ft_int_putstr_fd(char *s, int fd);
char	*ft_unsigned_itoa(unsigned int n);
int	ft_hexadec(unsigned long num, int flag);
int	ft_voidptr(void *addr);

#endif
