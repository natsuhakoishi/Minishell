/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:43:33 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:27:11 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t size)
{
	size_t			a;
	unsigned char	*str;

	a = 0;
	str = b;
	while (a < size)
	{
		*str++ = (unsigned char)c;
		a++;
	}
	return (b);
}
/*
#include <stdio.h>

int	main(void)
{
	char	a[10];
	int		b;

	b = 0;
	ft_memset(a, 'S', 5);
	while (b < 10)
	{
		printf("%c ", a[b]);
		b++;
	}
	printf("\n");
	return (0);
}
*/
