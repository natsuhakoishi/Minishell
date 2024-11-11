/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:37:08 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:25:47 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	a;

	while (n-- > 0)
	{
		a = *(unsigned char *)s1 - *(unsigned char *)s2;
		if (a != 0)
			return (a);
		s1++;
		s2++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	a[] = "haha";
	char	b[] = "hahb";
	size_t	n = 4;

	printf("%d\n", ft_memcmp(a, b, n));
	return (0);
}
*/
