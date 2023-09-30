/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaniel- <wdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:57:14 by wdaniel-          #+#    #+#             */
/*   Updated: 2023/03/14 18:52:58 by wdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int	i;
	static char	chr;

	if (sig == SIGUSR1)
		chr = chr | 0x01;
	if (i < 7)
		chr = chr << 0x01;
	i++;
	if (i == 8)
	{
		if (chr == 0)
			kill(info->si_pid, SIGUSR1);
		write(1, &chr, 1);
		i = 0;
		chr = 0;
	}
	usleep(10);
	kill(info->si_pid, SIGUSR2);
	(void) context;
}

int	main(void)
{
	int					pid;
	struct sigaction	sig;

	sig.sa_sigaction = ft_handler;
	sig.sa_flags = SA_SIGINFO;
	pid = getpid();
	write(1, "PID: ", 6);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	while (1)
		pause();
	return (0);
}
