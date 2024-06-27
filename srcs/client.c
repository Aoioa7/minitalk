/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aichida <aichida@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:22:43 by nrontey           #+#    #+#             */
/*   Updated: 2024/06/27 17:47:31 by aichida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static void	ft_exit_failure(void)
{
	write(1, "./client SERVER_PID MESSAGE\n", 29);
	exit(EXIT_FAILURE);
}

static void	retreive(int signal)
{
	static int	bytes_received = 0;

	if (signal == SIGUSR2)
		bytes_received++;
	else
	{
		ft_putnbr_fd(bytes_received, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

static void	send_signal(pid_t pid, char *str)
{
	int	i;
	int	j;

	j = -1;
	while (str[++j])
	{
		i = 8;
		while (i--)
		{
			if (str[j] >> i & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	int	len_str;

	len_str = ft_strlen(argv[2]);
	if (argc != 3 || !len_str || !ft_atoi(argv[1]))
		ft_exit_failure();
	ft_putstr_fd("Bytes sent        : ", STDOUT_FILENO);
	ft_putnbr_fd(len_str, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd("Bytes received    : ", STDOUT_FILENO);
	signal(SIGUSR1, retreive);
	signal(SIGUSR2, retreive);
	send_signal(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
