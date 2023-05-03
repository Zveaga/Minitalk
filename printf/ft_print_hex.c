/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_hex.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/14 14:42:33 by raanghel      #+#    #+#                 */
/*   Updated: 2023/01/19 12:35:58 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	len_hex(unsigned int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_print_hex(unsigned int n, char format)
{
	char	*dict;
	int		ret;

	ret = len_hex(n);
	if (n == 0)
		ret += 1;
	if (format == 'X')
		dict = "0123456789ABCDEF";
	else
		dict = "0123456789abcdef";
	if (n >= 0 && n < 16)
		ft_print_char(dict[n]);
	else
	{
		ft_print_hex((n / 16), format);
		ft_print_hex((n % 16), format);
	}
	return (ret);
}

// int	main(void)
// {
// 	printf("|%d", ft_print_hex(5151511));
// 	//printf ("%d\n", ft_print_hex(421));
// }

// int	ft_print_x(long int	n)
// {
// 	int				ret;
// 	int				i;
// 	long int		remainder;
// 	char			store_remainder[1000];

// 	i = 0;
// 	if (n < 0)
// 	{
// 		n *= -1;
// 		write(1, "-", 1);
// 	}
// 	if (n == 0)
// 		write(1, "0", 1);
// 	while (n != 0)
// 	{
// 		remainder = n % 16;
// 		n = n / 16;
// 		if (remainder <= 9)
// 			store_remainder[i++] = remainder + 48;
// 		else
// 			store_remainder[i++] = remainder + 55;
// 	}
// 	while (i >= 0)
// 		write(1, &store_remainder[i--], 1);
// 	ret = len_n(n);
// 	return (ret);
// }