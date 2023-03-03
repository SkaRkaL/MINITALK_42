/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:16:50 by sakarkal          #+#    #+#             */
/*   Updated: 2023/03/03 05:02:13 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_handler(int signal, siginfo_t *info, void *s)
{
	static char	c;
	static int	bit;
	static int	pid;

	(void)s;
	if (!pid)
		pid = info->si_pid;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		bit = 0;
		c = 0;
	}
	if (signal == SIGUSR1)
		c += (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (c != '\0')
			ft_putchar_fd(c, 1);
		else
			kill(pid, SIGUSR1);
		bit = 0;
		c = 0;
	}
}

static void	ft_pid_print(int pid)
{
	ft_putstr_fd("  \e[1;34;4m Server Bonus PID ➤ \e[0m   \e[0m", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n\n \e[038;5;243m  ✸  Waiting The Message... ✸\n\e[0m\n", 1);
}

int	main(void)
{
	struct sigaction	sig;
	int					pid;

	pid = getpid();
	ft_pid_print(pid);
	sig.sa_sigaction = ft_handler;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
