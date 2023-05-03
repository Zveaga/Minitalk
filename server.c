/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:02 by raanghel      #+#    #+#                 */
/*   Updated: 2023/05/03 11:12:33 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void _error(int pid)
{
	ft_printf("SERVER: unexpected error!\n");
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	string_end(int pid_client)
{
	ft_printf("\nMessage successfully received! Ready to receive another.\n");
		if (kill(pid_client, SIGUSR2) == -1)
			_error(pid_client);
}

void sig_handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0b11111111;
	static int	bits = 0;
	static int	mask = 0;

	(void) context;
	mask = 0b10000000;
	if (signum == SIGUSR1)       // "0" is received
		c = c ^ (mask >> bits);  
	else if (signum == SIGUSR2)  // "1" is received
		c = c | (mask >> bits);
	bits++;
	if (bits == 8 && c != '\0')
	{
		write(1, &c, 1);
		bits = 0;
		c = 0b11111111;
	}
	if (c == '\0')
	{
		string_end(info->si_pid);
		c = 0b11111111;
		bits = 0;
	}	
	if (kill(info->si_pid, SIGUSR1) == -1)
		_error(info->si_pid);
}
int	main(void)
{
	pid_t				pid;
	struct sigaction 	action;
	
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	action.sa_flags = SA_RESTART | SA_NODEFER;
	action.sa_sigaction = sig_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}