/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/10 14:54:18 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

volatile int bit_confirmed = 0;
char *string = NULL;

void	_error()
{
	printf("CLIENT: unexpected error!");
	exit(EXIT_FAILURE);
}

void	send_bit(char *message, int pid)
{
	int 	bits;
	int 	mask;
	int		i;

	bits = 0;
	mask = 0b10000000;
	i = 0;
		
	while (message[i])
	{
		bits = 0;
		while (bits++ < 8)
		{
			bit_confirmed = 0;
			if (message[i] & mask)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while(!bit_confirmed);
			mask >>= 1;
		}
		i++;
		mask = 0b10000000;
	}
}

void	SIGUSR_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		bit_confirmed = 1;
		usleep(100);
	}
	else if (signum == SIGUSR2)
	{
		printf("Message successfully sent!\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	int					i;
	struct sigaction	action;
	i = 0;
	if (argc != 3)
	{	printf("Client: Invalid argument number!\n");
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	action.sa_flags = SA_RESTART | SA_SIGINFO;
	action.sa_handler = SIGUSR_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	send_bit(argv[2], pid);
	send_bit("\n", pid);
	return (0);
}



// void	send_bit(char c, int pid)
// {
// 	int 	bits;
// 	int 	mask;

// 	bits = 0;
// 	mask = 0b10000000;
// 	while (bits++ < 8)
// 	{
// 		bit_confirmed = 0;
// 		if (c & mask)
// 		{
// 			if(kill(pid, SIGUSR2) == -1)
// 				_error();
// 		}
// 		else
// 			kill(pid, SIGUSR1);
// 		while(!bit_confirmed);
// 		mask >>= 1;
// 	}
// }