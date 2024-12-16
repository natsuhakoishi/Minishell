/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:05:13 by yyean-wa          #+#    #+#             */
/*   Updated: 2024/12/16 15:12:01 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;

	if (size == 0)
		return (src_len);

	i = 0;
	while (src[i] && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (src_len);
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
