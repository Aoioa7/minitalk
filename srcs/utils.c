/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aichida <aichida@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:52:07 by aichida           #+#    #+#             */
/*   Updated: 2024/06/27 18:20:36 by aichida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	x;

	x = n;
	if (x < 0)
	{
		ft_putchar_fd('-', fd);
		x *= -1;
	}
	if (x < 10)
		ft_putchar_fd(x + '0', fd);
	else
	{
		ft_putnbr_fd(x / 10, fd);
		ft_putchar_fd(x % 10 + '0', fd);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int		n;
	int		sig;
	size_t	i;

	n = 0;
	sig = 1;
	i = 0;
	while (s[i] == ' ' || ('\t' <= s[i] && s[i] <= '\r'))
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
	{
		sig *= -1;
		i++;
	}
	while ('0' <= s[i] && s[i] <= '9')
	{
		n *= 10;
		n += s[i] - '0';
		i++;
	}
	return (n * sig);
}
