/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aichida <aichida@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:02:28 by aichida           #+#    #+#             */
/*   Updated: 2024/06/28 06:50:04 by aichida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// error-handling

static void	failure(void)
{
	ft_putstr_fd("format error :\n./client [SERVER_PID] \"MESSAGE\"\n", 1);
	exit(1);
}

// S1c = 1, S2c = 0, S1s is not null, S2c is null

// if catch SIGUSR2, one char (1byte = 8 bits) add
// if catch SIGUSR1, write how many chars were added
// called 1 when handler(server-side) called 8

static void	signal_handler(int sig)
{
	static int	len = 0;

	if (sig == SIGUSR2)
		len++;
	else if (sig == SIGUSR1)
	{
		ft_putstr_fd("\nBytes-received: ", 1);
		ft_putnbr_fd(len, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

// char * > char = 1byte = 8bits
// if bit = 1, send SIGUSR1
// if bit = 0, send SIGUSR2
// send string from 0 to len(string) - 1
// send char (from 2**7 to 2**0) over 8 bits using kill()
// usleep(5) -> 5 micro seconds
// second while -> create and send 00000000(='\0')

static void	send_signals(pid_t pid, char *s)
{
	int	i;
	int	j;

	j = 0;
	while (s[j])
	{
		i = 8;
		while (i--)
		{
			if ((s[j] >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		j++;
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		usleep(100);
	}
}

// strlen -> argv[2] ->  segmentation fault risk
// if argc = 1, argv[1] = null
// send_signals * 8 -> signal_handler(client-side) * 1

int	main(int argc, char *argv[])
{
	int	len;

	if (argc != 3 || !ft_atoi(argv[1]))
		failure();
	len = ft_strlen(argv[2]);
	if (!len)
		failure();
	ft_putstr_fd("Bytes-sent: ", 1);
	ft_putnbr_fd(len, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	send_signals(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
