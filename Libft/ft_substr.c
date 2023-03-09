/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 12:22:05 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/11 17:36:04 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub_str;
	int				i;
	unsigned int	len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (len_s <= start)
		len = 0;
	else if (len_s - start < len)
		len = len_s - start;
	sub_str = (char *) malloc ((len + 1) * sizeof(char));
	if (sub_str == NULL)
		return (NULL);
	while (len > 0 && start < len_s)
	{
		sub_str[i] = s[start];
		i++;
		start++;
		len--;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

// int main1(void)
// {
// 	char *s = "";
// 	char *sub_str;

// 	sub_str = ft_substr(s, 1, 1);

// 	printf("%s\n", sub_str);
// 	free(sub_str);
// 	return(1);
// }

// int main(void)
// {
// 	main1();
// 	while(1);
// }