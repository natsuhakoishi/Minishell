/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:37:59 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:26:45 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char				*dest_ptr;
	const unsigned char	*src_ptr;
	size_t				a;

	a = 0;
	dest_ptr = dest;
	src_ptr = src;
	if (!dest && !src)
		return (dest);
	if (dest < src)
	{
		while (a++ < n)
			*dest_ptr++ = *src_ptr++;
	}
	else
	{
		dest_ptr += n;
		src_ptr += n;
		while (n-- != 0)
			*--dest_ptr = *--src_ptr;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	src[] = "No way";
	char	dest[10];

	ft_memmove(dest, src, 2);
	printf("%s\n", dest);
	return (0);
}
*/
