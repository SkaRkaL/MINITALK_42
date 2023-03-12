/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 00:42:11 by sakarkal          #+#    #+#             */
/*   Updated: 2023/03/12 20:08:27 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		usleep(800);
		bit++;
	}
}

void	ft_send_message(int pid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		ft_bit_sender(pid, msg[i]);
		i++;
	}
	ft_bit_sender(pid, '\n');
	ft_bit_sender(pid, '\0');
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	i = 0;
	if (ac == 3 && av[2][0] != '\0')
	{
		pid = ft_atoi(av[1]);
		for (int j = 0; av[1][j]; j++)
		{
			if (!isdigit(av[1][j])){
				return(write(2,"\e[033;0;31m	⚡︎   ❌ Error PID ❌	⚡\e[0m\n", 48));
			}
		}
		if (pid <= 0)
		{
			ft_putstr_fd("\e[033;0;31m ⚡︎⚡︎ ❌ Ops, Error PID ❌ ⚡︎⚡︎\e[0m\n", 2);
			return (0);
		}
		ft_send_message(pid, av[2]);
	}
	else
	{
		ft_putstr_fd("\e[033;0;31m→  Error: Wrong Format\e[0m\n", 2);
		ft_putstr_fd("\e[033;0;35m→  Try: ./client [PID] [MESSAGE]\e[0m\n", 2);
	}
	return (0);
}
