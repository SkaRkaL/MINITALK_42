/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:16:42 by sakarkal          #+#    #+#             */
/*   Updated: 2023/02/27 22:31:26 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ha.h"

static void	succeeded(int signal)
{
	if (signal == SIGUSR1)
		ft_putstr_fd("\e[033;0;32m→ Server received message ✅\e[0m\n", 1);
	exit (0);
}

static void	ft_bit_sender(int pid, char chara)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((chara & (1 << bit)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				write (2, "\e[033;0;31m→  PID not correct. ❌\e[0m\n", 47);
				exit(0);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				write (2, "\e[033;0;31m→  PID not correct. ❌\e[0m\n", 47);
				exit(0);
			}
		}
		usleep(860);
		bit++;
	}
}

static void	ft_send_str(int pid, char input[])
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		ft_bit_sender(pid, input[i]);
		i++;
	}
	ft_bit_sender(pid, '\n');
	ft_bit_sender(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3 && argv[2][0] != '\0')
	{
		pid = ft_atoi(argv[1]);
		if (pid <= 0)
		{
			ft_putstr_fd("\e[033;0;31m ⚡︎⚡︎ ❌ Ops, Error PID ❌ ⚡︎⚡︎\e[0m\n", 2);
			return (0);
		}
		signal(SIGUSR1, succeeded);
		ft_send_str(pid, argv[2]);
		while (1)
			pause();
	}
	else
	{
		ft_putstr_fd("\e[033;0;31m→  Error: Wrong Format\e[0m\n", 2);
		ft_putstr_fd("\e[033;0;35m→  Try: ./client [PID] [MESSAGE]\e[0m\n", 2);
	}
	return (0);
}
