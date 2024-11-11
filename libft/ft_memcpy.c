/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:20:02 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:26:18 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	a;
	char	*dest_ptr;
	char	*src_ptr;

	a = 0;
	if (!dest && !src)
		return (dest);
	dest_ptr = dest;
	src_ptr = (char *)src;
	while (a < n)
	{
		*dest_ptr++ = *src_ptr++;
		a++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	src[] = "I am a newbies.";
	char	dest[20];

	ft_memcpy(dest, src, 12);
	printf("%s\n", dest);
	return (0);
}
*/
