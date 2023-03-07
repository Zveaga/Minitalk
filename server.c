/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:02 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/07 11:50:49 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"


void SIGUSR_handler(int signum, siginfo_t *info, void *context)
{
	static char	c = 0b11111111;
	static int	bits = 0;
	int	mask;
	(void)info;
	(void)context;
	
	mask = 0b10000000;
	// if SIGUSR1 is received, 0 is received 
	if (signum == SIGUSR1)
	{
		c = c ^ (mask >> bits);
	}
	// if SIGUSR2 is received, 1 is received 
	else if (signum == SIGUSR2)
	{
		c = c | (mask >> bits);
	}
	bits++;
	if (bits == 8)
	{
		printf("%c", c);
		bits = 0;
		c = 0b11111111;
	}
}

int	main(void)
{
	pid_t	pid;
	struct sigaction action;
	
	pid = getpid();
	printf("Server PID: %d\n", pid);
	
	action.sa_sigaction = SIGUSR_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}