/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 13:41:37 by raanghel      #+#    #+#                 */
/*   Updated: 2023/01/19 12:36:10 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdarg.h>
# include<unistd.h>

int		ft_print_char(int c);

int		ft_print_str(char *str);

int		ft_print_d_i(long int n);

int		ft_print_u(unsigned int n);

int		ft_print_hex(unsigned int n, char format);

int		ft_print_ptr(unsigned long n);

int		len_n(long int n);

int		len_hex(unsigned int n);

int		ft_printf(const char *str, ...);

#endif