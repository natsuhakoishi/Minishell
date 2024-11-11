/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:05:13 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:36:51 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	a;

	a = 0;
	if (size > 0)
	{
		while (*src && a + 1 < size)
		{
			*dest++ = *src++;
			a++;
		}
	}
	if (a < size)
		*dest = '\0';
	while (*src++)
		a++;
	return (a);
}
/*
#include <stdio.h>

int	main(void)
{
	char	src[] = "Good Morning China!";
	char	dest[20];
	size_t	a;

	a = ft_strlcpy(dest, src, 13);

	printf("%ld\n", a);
	printf("%s\n", dest);
	return (0);
}
*/
