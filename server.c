/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:02 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/10 13:16:33 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void _error(int pid)
{
	printf("SERVER: unexpected error!");
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

// void	append_char(char c, char *message)
// {
	
// }

void SIGUSR_handler(int signum, siginfo_t *info, void *context)
{
	static	char	c = 0b11111111;
	static	int		bits = 0;
	static	int		pid_client = 0;
	static	int		mask = 0;
	//static	char	*message;
	(void)			context;
	
	mask = 0b10000000;
	pid_client = info->si_pid;
	if (signum == SIGUSR1)       // "0" is received
		c = c ^ (mask >> bits);  
	 
	else if (signum == SIGUSR2)  // "1" is received
		c = c | (mask >> bits);
	bits++;
	if (bits == 8)               // Receive 1 char
	{
		write(1, &c, 1);
		bits = 0;
		c = 0b11111111;
	}
	kill(info->si_pid, SIGUSR1);
	//_error(pid_client);
	if (c == 0)
	{
		printf("End of message!\n");
		kill(info->si_pid, SIGUSR2);
	}
	
}

int	main(void)
{
	pid_t				pid;
	struct sigaction 	action;
	
	pid = getpid();
	printf("Server PID: %d\n", pid);
	action.sa_flags = SA_SIGINFO | SA_RESTART;
	action.sa_sigaction = SIGUSR_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}