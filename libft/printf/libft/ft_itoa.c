/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkarabab <bkarabab@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:14:34 by bkarabab          #+#    #+#             */
/*   Updated: 2025/10/13 18:59:09 by bkarabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_handle_charge_and_process(long nb, int length, int charge);
static void	ft_putnbr(char *buff, long n, int i, int length);
static int	ft_get_len(int n);

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;
	int		charge;
	int		length;

	if (n == 0)
		return (ft_strdup("0"));
	nb = n;
	length = ft_get_len(n);
	if (nb < 0)
		charge = -1;
	else
		charge = 0;
	s = ft_handle_charge_and_process(nb, length, charge);
	if (!s)
		return (ft_strdup("0"));
	return (s);
}

static char	*ft_handle_charge_and_process(long nb, int length, int charge)
{
	char	*s;

	if (charge == -1)
	{
		s = ft_calloc(length + 2, sizeof(char));
		if (!s)
			return (0);
		s[0] = '-';
		ft_putnbr(s + 1, -nb, 0, length);
	}
	else
	{
		s = ft_calloc(length + 1, sizeof(char));
		if (!s)
			return (0);
		ft_putnbr(s, nb, 0, length);
	}
	return (s);
}

static int	ft_get_len(int n)
{
	int	length;

	length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static void	ft_putnbr(char *buff, long n, int i, int length)
{
	if (n >= 10)
		ft_putnbr(buff, n / 10, i + 1, length);
	buff[length - i - 1] = '0' + (n % 10);
}
/*
int	main(void)
{
	int a = 123456;
	int b = -123456;
	int c = 0;
	int d = 2147483647;
	int e = -2147483648;
	long f = 2147483648;
	long g = -2147483649;

	printf("%s\n", ft_itoa(a));
	printf("%s\n", ft_itoa(b));
	printf("%s\n", ft_itoa(c));
	printf("%s\n", ft_itoa(d));
	printf("%s\n", ft_itoa(e));
	printf("%s\n", ft_itoa(f));
	printf("%s\n", ft_itoa(g));
}
*/
