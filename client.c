/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/09 19:13:52 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

volatile int bit_confirmed = 0;

void	_error()
{
	printf("CLIENT: unexpected error!");
	exit(EXIT_FAILURE);
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
// int	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*dup;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	len = ft_strlen(s);
// 	dup = malloc(sizeof(char) * (len + 1));
// 	if (dup == NULL)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
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
			{
				if(kill(pid, SIGUSR2) == -1)
					_error();
			}
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
		usleep(10);
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
	action.sa_flags = SA_RESTART;
	action.sa_handler = SIGUSR_handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	
	send_bit(argv[2], pid);
	// while (argv[2][i] != '\0')
	// {
	// 	send_bit(argv[2][i], pid);
	// 	i++;
	// }
	// int	j;

	// j = 0;
	
	// while (j++ != 8)
	// 	kill(pid, SIGUSR1);
	send_bit("\n", pid);
	return (0);
}
