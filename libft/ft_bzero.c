/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyean-wa < yyean-wa@student.42kl.edu.my    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:09:14 by yyean-wa          #+#    #+#             */
/*   Updated: 2023/10/30 16:11:15 by yyean-wa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	a;

	str = s;
	a = 0;
	while (a < n)
	{
		*str++ = '\0';
		a++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	char	a[20] = "Hello, World";
	int		b;

	b = 0;
	ft_bzero(a, 5);
	while (b < 20)
	{
		printf("%c", a[b]);
		b++;
	}
	printf("\n");
	return (0);
}
*/
