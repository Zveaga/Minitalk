/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/05/05 20:10:09 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

volatile int	g_bit_confirmed = 0;

void	_error(void)
{
	ft_printf("CLIENT: unexpected error!\n");
	exit(EXIT_FAILURE);
}

void	send_char(char c, int pid, int mask)
{
	if (c & mask)
	{
		if (kill(pid, SIGUSR2) == -1)
			_error();
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
			_error();
	}
}

void	send_message(char *message, int pid)
{
	static int	bits = 0;
	static int	mask = 0b10000000;
	int			i;

	i = 0;
	while (1)
	{
		while (bits++ < 8)
		{
			g_bit_confirmed = 0;
			send_char(message[i], pid, mask);
			while (!g_bit_confirmed)
				;
			mask >>= 1;
		}
		i++;
		bits = 0;
		mask = 0b10000000;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
		g_bit_confirmed = 1;
	else if (signum == SIGUSR2)
	{
		ft_printf("Message successfully sent!\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	int					pid;			
	struct sigaction	action;

	if (argc != 3)
	{
		ft_printf("Client: Invalid argument number!\n");
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	action.sa_handler = sig_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	send_message(argv[2], pid);
	send_message("\n", pid);
	return (0);
}
