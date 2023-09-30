/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaniel- <wdaniel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:31:07 by wdaniel-          #+#    #+#             */
/*   Updated: 2023/03/14 19:32:37 by wdaniel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	sig_msg(int signal)
{
	if (signal == SIGUSR1)
		write(1, "\033[1;5;35mYour message has been sent !\n", 38);
}

static void	bit_send(int pid, char *str)
{
	int		bit;
	char	chr;

	while (*str)
	{
		chr = *str++;
		bit = 8;
		while (bit)
		{
			signal(SIGUSR2, sig_msg);
			if ((0x01 << --bit) & chr)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			sleep(1);
		}
	}
	bit = 8;
	while (bit--)
	{
		signal(SIGUSR1, sig_msg);
		signal(SIGUSR2, sig_msg);
		kill(pid, SIGUSR2);
		sleep(1);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
		return (write (1, "\033[1;5;36mOpss, invalid arguments !\n", 32));
	pid = ft_atoi(argv[1]);
	bit_send(pid, argv[2]);
	return (0);
}
