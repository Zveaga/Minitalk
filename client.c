/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/14 18:36:02 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

volatile int bit_confirmed = 0;

void	_error()
{
	printf("CLIENT: unexpected error!");
	exit(EXIT_FAILURE);
}

void	send_null(int pid)
{
	static int	i = 0;
	
	while (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			_error();
	}
	i = 0;
}

void	send_bit(char *message, int pid)
{
	int	bits = 0;
	int	mask = 0b10000000;
	int	i;
	
	i = 0;
	while (message[i])
	{
		while (bits++ < 8)
		{
			bit_confirmed = 0;
			if (message[i] & mask)
			{
				if (kill(pid, SIGUSR2) == -1)
					_error();
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					_error();
			}
			while(!bit_confirmed);
			mask >>= 1;
		}
		// if (message[i] == '\0')
		// {
		// 	printf("NULL");
		// 	send_null(pid);
		// 	//break;
		// }
		i++;
		bits = 0;
		mask = 0b10000000;
	}
	//send_null(pid);
}

void	SIGUSR_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		bit_confirmed = 1;
	}
	else if (signum == SIGUSR2)
	{
		printf("\nMessage successfully sent!\n");
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
	//action.sa_flags = SA_NODEFER;
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