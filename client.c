/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/08 18:28:49 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

volatile int bit_confirmed = 0;

// int	send_null(int pid, char *str)
// {
// 	static int	i = 0;

// 	if (i++ != 8)
// 	{
// 		if (kill(pid, SIGUSR1) == -1)
// 			error(str);
// 		return (0);
// 	}
// 	return (1);
// }

void	_error()
{
	printf("CLIENT: unexpected error!");
	exit(EXIT_FAILURE);
}

void	send_bit(char c, int pid)
{
	static	int 	bits;
	static	int 	mask;

	bits = 0;
	mask = 0b10000000;
	while (bits++ < 8)
	{
		bit_confirmed = 0;
		if (c & mask)
		{
			if(kill(pid, SIGUSR2) == -1)
				_error();
		}
		else
			kill(pid, SIGUSR1);
		while(!bit_confirmed);
		mask >>= 1;
	}
}

void	SIGUSR_handler(int signum)
{
	if (signum == SIGUSR1)
		bit_confirmed = 1;
}

int	main(int argc, char *argv[])
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
	action.sa_flags = SA_RESTART | SA_NODEFER;
	action.sa_handler = SIGUSR_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (argv[2][i] != '\0')
	{
		send_bit(argv[2][i], pid);
		i++;
	}
	send_bit('\n', pid);
	// if (argv[2][i] == '\0')
	// 	{
	// 		int	j;

	// 		j = 0;
	// 		while (j++ < 8)
	// 		{
	// 			if (kill(pid, SIGUSR1) == -1)
	// 				error();
	// 		}
	// 	}
	// return (0);
}
