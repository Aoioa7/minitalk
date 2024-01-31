/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:56:10 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/31 13:24:21 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	retreive(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;
	pid_t					pid_client;

	(void)context;
	if (info->si_pid)
		pid_client = info->si_pid;
	c = c | (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(pid_client, SIGUSR1);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(pid_client, SIGUSR2);
	}
	else
		c = c << 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;
	pid_t				pid_server;

	pid_server = getpid();
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(pid_server, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_sigaction = retreive;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
