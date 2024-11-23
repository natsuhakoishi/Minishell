/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:39:14 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:42:22 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;

	str = s;
	while (n-- > 0)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	const char*	str = "Happy New Year!";
	char	c = 'w';
	size_t	len = 9;

	if (ft_memchr(str, c, len) != NULL)
	{
		printf("%c found in string.\n", c);
	}
	else
	{
		printf("Not found.\n");
	}
	return (0);
}
*/
