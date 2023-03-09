/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: raanghel <raanghel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 17:30:18 by raanghel      #+#    #+#                 */
/*   Updated: 2022/11/16 19:33:08 by raanghel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<string.h>
#include<stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}

	while (i < len && haystack[i]) // loop throuh the haystack
	{
		j = 0;
		while (needle[j] && (i + j) < len)   // loop throug the needle
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;  // move needle to the right until it matches with haystack 
		}

		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (0);
}

// int main(void)
// { 
// 	char *s1 = "MZIRIBMZIRIBMZE123";
//  	char *s2 = "MZIRIBMZE";

// 	printf("Own:  %s\n", ft_strnstr(s1, s2, 18));
// 	printf("Real: %s\n", strnstr(s1, s2, 18));
//  }

