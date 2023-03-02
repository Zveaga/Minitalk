/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:02 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/02 17:21:14 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"


void SIGUSR_handler(int signum)
{
	static char	c = 0b11111111;
	static int	bits = 0;
	int	mask;
	
	mask = 0b10000000;	
	if (signum == SIGUSR1)
	{
		printf("0");
		c = c ^ (mask >> bits);	
	}
	else if (signum == SIGUSR2)
	{
		printf("1");
		c = c | (mask >> bits);
	}
	bits++;
	if (bits == 8)
	{
		printf(" --> %c\n", c);
		bits = 0;
		c = 0b11111111;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("Server PID: %d\n", pid);
	signal(SIGUSR1, SIGUSR_handler);
	signal(SIGUSR2, SIGUSR_handler);
	while (1)
		pause();
}