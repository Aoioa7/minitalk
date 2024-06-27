/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aichida <aichida@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:02:16 by aichida           #+#    #+#             */
/*   Updated: 2024/06/28 06:40:55 by aichida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// count -> saves how many signals came (reset when 8)
// tmp_c -> saves char to put (modify bits step by step)

// if SIGUSR1, stand 1 at the end of tmp_c bits
// if SIGUSR2, 0

// when count = 8, tmp_c is prepared to put or null (all SIGUSR2, all 0)
// -> send a signal to client -> client send 8 then server send 1
// count == 8 -> 0 -> 1

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	count = 1;
	static char	tmp_c = 0;
	pid_t		client_pid;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	tmp_c |= (sig == SIGUSR1);
	if (count == 8)
	{
		count = 0;
		if (!tmp_c)
			kill(client_pid, SIGUSR1);
		else
		{
			ft_putchar_fd(tmp_c, 1);
			tmp_c = 0;
			kill(client_pid, SIGUSR2);
		}
	}
	else
		tmp_c <<= 1;
	count++;
}

// start this program -> display information -> config server
// -> wait for & response to signals

int	main(void)
{
	struct sigaction	server_sigaction;
	pid_t				server_pid;

	server_pid = getpid();
	ft_putstr_fd("Server-PID: ", 1);
	ft_putnbr_fd(server_pid, 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&server_sigaction.sa_mask);
	server_sigaction.sa_sigaction = signal_handler;
	server_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &server_sigaction, 0);
	sigaction(SIGUSR2, &server_sigaction, 0);
	while (1)
		pause();
	return (0);
}
