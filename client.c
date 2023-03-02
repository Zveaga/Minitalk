/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/02 17:38:12 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void push_signal(char *letter, int pid)
{
	int	i;
	int	j;
	int	mask;

	i = 0;
	j = 0;
	mask = 0b10000000;
	while (j++ < 8)
	{
		if (letter[i] & mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		mask >>= 1;
		usleep(3);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;
	
	if (argc != 3)
	{	printf("Client: Invalid argument number!\n");
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	push_signal(argv[2], pid);
	return (0);
}
