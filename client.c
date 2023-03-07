/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 12:54:07 by raanghel      #+#    #+#                 */
/*   Updated: 2023/03/07 12:00:04 by rares         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void send_bit(char c, int pid)
{
	int	bits;
	int	mask;

	bits = 0;
	mask = 0b10000000;
	while (bits++ < 8)
	{
		if (c & mask)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		mask >>= 1;
		usleep(50);
	}
}

void	SIGUSR_handler(int signum)
{
	
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;
			
	i = 0;
	if (argc != 3)
	{	printf("Client: Invalid argument number!\n");
		exit(EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	while (argv[2][i] != '\0')
	{
		send_bit(argv[2][i], pid);
		i++;
	}
	send_bit('\n', pid);
	return (0);
}
