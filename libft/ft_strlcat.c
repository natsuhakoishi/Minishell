/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:38:07 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 22:12:50 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dl;
	size_t	sl;
	size_t	len;

	if (size == 0 && !dest)
		return (0);
	dl = 0;
	sl = 0;
	while (dest[dl] && dl < size)
		dl++;
	while (src[sl])
		sl++;
	if (dl >= size)
		return (size + sl);
	len = 0;
	while (src[len] && len + dl + 1 < size)
	{
		dest[dl + len] = src[len];
		len++;
	}
	dest[dl + len] = '\0';
	return (dl + sl);
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[20] = "I am ... ";
	char	src[] = "solips";
	size_t	len;

	len = ft_strlcat(dest, src, 12);
	printf("%s\n", dest);
	printf("%ld\n", len);
	return (0);
}
*/
