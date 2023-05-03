/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_ptr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/13 14:24:04 by raanghel      #+#    #+#                 */
/*   Updated: 2023/01/19 12:36:00 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	len_ptr(unsigned long n)
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

int	ft_print_ptr(unsigned long n)
{
	char	*dict;
	int		ret;

	ret = len_ptr(n);
	dict = "0123456789abcdef";
	if (n == 0)
		ret += 1;
	if (n >= 0 && n < 16)
		ft_print_char(dict[n]);
	else
	{
		ft_print_ptr(n / 16);
		ft_print_ptr(n % 16);
	}
	return (ret);
}
