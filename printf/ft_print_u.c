/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_u.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/23 12:20:38 by raanghel      #+#    #+#                 */
/*   Updated: 2023/01/19 12:36:03 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

int	ft_print_u(unsigned int n)
{
	int	ret;

	ret = 0;
	ret = len_n(n);
	if (n >= 0 && n <= 9)
	{
		n += '0';
		write(1, &n, 1);
	}
	else
	{
		ft_print_u(n / 10);
		ft_print_u(n % 10);
	}
	return (ret);
}
